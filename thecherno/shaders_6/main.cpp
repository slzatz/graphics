/* This program based on a TheCherno video creates, compiles and displays an opengl shader
 * There was some modification necessary some modification was necessary and I found it in
 * a comment on the TheCherno video that this is based on.
 *
 * Turns out the problem was that TheCherno was running in compatibility mode
 * and were were running in core mode and in core mode you have to explicitly
 * declare a vertex array.
 *
 * Chad Cravens in the comments wrote the following:
 *
 *  unsigned int buffer, vao; // added vao variable
 *  glGenVertexArrays(1, &vao); // added this function
 *  glGenBuffers(1, &buffer);
 *  glBindVertexArray(vao); // added this function after glGenBuffers()
 *  glBindBuffer(GL_ARRAY_BUFFER, buffer);
 *  glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);
 *
 * This program uses uniforms
 * Probably this program is quite similar to shaders_5
 *
 * Note GLFW provides methods to manage windows with OpenGL contexts.
 * GLEW is the OpenGL Extension Wrangler but it looks like GLEW is importing
 * all the OpenGL functions/methods
*/

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct ShaderProgramSource
{
    string VertexSource;
    string FragmentSource;
};

static ShaderProgramSource ParseShader(const string& filepath)
{
    ifstream stream(filepath);
    string line;
    stringstream ss[2];

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        cout << line << endl;

        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;

    }
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetProgramInfoLog(id, length, &length, message);
        cout << "Failed to link shader!" << endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;

    }
    return id;
}

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    /* This line had to be added below because mesa/opengl 1.30
     * doesn't support the shader code:  layout (location = 0) ...
     * but the line below apparently does the same thing
     * see https://stackoverflow.com/questions/21354301/glsl-syntax-problems-unexpected-new-identifier
     */
    //not necessary with layout gone
    // not necessary with layout in using 440 or ?330
    //glBindAttribLocation(program, 0, "vertexPosition_modelspace");

    glLinkProgram(program);
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}
int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;


    //glfwDefaultWindowHints();
    //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //thee is a compatibility profile GLFW_OPENGL_COMPAT_PROFILE
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // apparently only for Mac

    window = glfwCreateWindow(640, 480, "Hello Steve", NULL, NULL); //
    if (!window){

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // glewInit must come after the above since need valid opengl context before calling it
    if (glewInit() != GLEW_OK)
        cout << "Error!" << endl;

    cout << "GL_VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5,

        //0.5f, 0.5f,
        -0.5f, 0.5f,
        //-0.5f, -0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // generating a buffer and giving back an id
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderProgramSource source = ParseShader("basic_shader");

    cout << "VERTEX" << endl;
    cout << source.VertexSource << endl;
    cout << "FRAGMENT" << endl;
    cout << source.FragmentSource << endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    //ASSERT
    float r = 0.0f;
    float increment = 0.05f;

    while (!glfwWindowShouldClose(window)) {

        glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glUniform4f(location, r, 0.3f, 0.8f, 1.0f); // location is where the uniform "u_Color" is stored
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1.0f) increment = -0.05f;
        else if (r < 0.0f) increment = 0.05f;
        r += increment;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
