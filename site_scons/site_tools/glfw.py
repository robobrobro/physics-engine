import os

def exists(env):
    return True

def generate(env):
    env.Append(
        LIBS = [
            'glfw3',
        ],
    )

    glfw_path = os.environ.get('GLFW_PATH')

    if glfw_path is None:
        return

    if not os.path.isabs(glfw_path):
        glfw_path = os.path.join(os.path.abspath(str(env.Dir('#'))), glfw_path)

    env['GLFW_PATH'] = glfw_path

    env.Append(
        CPPPATH = [
            '$GLFW_PATH/include',
        ],
        LIBPATH = [
            '$GLFW_PATH/src',
        ],
    )
