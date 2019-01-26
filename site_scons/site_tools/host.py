def exists(env):
    return True

def generate(env):
    env.Replace(OS='$HOST_OS')
