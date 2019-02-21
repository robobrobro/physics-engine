def exists(env):
    return True

def generate(env):
    env.Append(
        LIBS = [
            'opengl32',
            'X11',
        ],
    )
