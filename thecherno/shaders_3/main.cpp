/* This program based on a TheCherno video creates, compiles and displays an opengl shader
 * There was some modification necessary some modification was necessary and I found it in
 * a comment on the TheCherno video that this is based on.
 * Chad Cravens in the comments wrote the following:
 *
 *  unsigned int buffer, vao; // added vao variable
 *  glGenVertexArrays(1, &vao); // added this function
 *  glGenBuffers(1, &buffer);
 *  glBindVertexArray(vao); // added this function after glGenBuffers()
 *  glBindBuffer(GL_ARRAY_BUFFER, buffer);
 *  glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);
 *
 * Somehow in this version I could use the exact shader code from TheCherno
 * and not have to use the code from the tutorial below although
 * shader_2 used that code.
 *
 * Also needed to use the shader code from this tutorial:
 *     http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
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

    //glewExperimental = true; //unnecessary

    if (!glfwInit())
        return -1;


    //glfwDefaultWindowHints();
    //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // apparently only for Mac

    window = glfwCreateWindow(640, 480, "Hello Steve", NULL, NULL); //
    if (!window){

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // glewInit must come after the above since need valid opengl context before calling it
    //glewExperimental = true; //unnecessary
    if (glewInit() != GLEW_OK)
        cout << "Error!" << endl;

    cout << "GL_VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f, //0.0, 0.5
        0.5f, -0.5f

    };
    // generating a buffer and giving back an id
    unsigned int buffer,  vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &buffer);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //orig

    ShaderProgramSource source = ParseShader("basic_shader");

    cout << "VERTEX" << endl;
    cout << source.VertexSource << endl;
    cout << "FRAGMENT" << endl;
    cout << source.FragmentSource << endl;

    /*
    // the below from TheCherno did not work for me - not sure why
    string vertexShader_ =
           "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec4 position;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position = position;\n"
            "}\n";

    // this works and came from tutorial mentioned at beginning of program
    string vertexShader =
           "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position.xyz = vertexPosition_modelspace;\n"
            "    gl_Position.w = 1.0;\n"
            "}\n";

    // the below from TheCherno did not work for me - not sure why
    string fragmentShader_ =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0, 1.0, 0.0, 1.0);\n"
            "}\n";

    // this works and came from tutorial mentioned at beginning of program
    string fragmentShader =
            "#version 330 core\n"
            "\n"
            "out vec3 color;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   color = vec3(1, 0, 0);\n"
            "}\n";
     */

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDisableVertexAttribArray(0); //does not work if this is here
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
