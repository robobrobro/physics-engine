def exists(env):
    return True

def generate(env):
    env.Replace(MODE='debug')
    env.Append(CCFLAGS='-g')
