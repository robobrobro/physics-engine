def exists(env):
    return True

def generate(env):
    env.Replace(MODE='release')
    env.Append(
        CCFLAGS = '-O3',
        LINKFLAGS = '-s',
    )
