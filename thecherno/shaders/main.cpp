/* This program based on a TheCherno video creates, compiles and displays an opengl shader
 * There was some modification necessary since it appears that the version of opengl that
 * arch uses is mesa and if I am understanding correctly it's a pretty old version of
 * opengl.  The necessary changes are noted in the code*/

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

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
    glBindAttribLocation(program, 0, "vertexPosition_modelspace");

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

    ////glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    ////glfwWindowHint(GLFW_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    ////glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    window = glfwCreateWindow(1000, 1000, "Goodbye World", NULL, NULL);
    if (!window){

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // glewInit must come after the above since need valid opengl context before calling it
    if (glewInit() != GLEW_OK)
        cout << "Error!" << endl;

    cout << glGetString(GL_VERSION) << endl;

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f, //0.0, 0.5
        0.5f, -0.5f

    };
    // generating a buffer and giving back an id
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // note layout (location = 0) not supported until opengl 1.40 and we have 1.30
    string vertexShader =
           //"#version 330 core\n"
            "#version 130\n"
            "\n"
            //"layout(location = 0) in vec4 position;\n"
            "in vec3 vertexPosition_modelspace;\n"
            //"in vec4 position;\n"
            "\n"
            "void main()\n"
            "{\n"
            //"gl_Position = position;\n"
            "gl_Position.xyz = vertexPosition_modelspace;\n"
            "gl_Position.w = 1.0;\n"
            "};\n";

    string fragmentShader =
            "#version 130\n"
            //"#version 330 core\n"
            "\n"
            //"layout(location = 0) out vec4 color;\n"
            "out vec4 color;\n"
            "\n"
            "void main()\n"
            "{\n"
            "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "};\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, ...) if we had index buffer

        /*
        // below is legacy opengl
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        */

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
