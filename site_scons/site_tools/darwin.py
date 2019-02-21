def exists(env):
    return True

def generate(env):
    env.Append(
        LINKFLAGS = [
            '-framework', 'Cocoa',
            '-framework', 'CoreVideo',
            '-framework', 'IOKit',
            '-framework', 'OpenGL',
        ],
    )
