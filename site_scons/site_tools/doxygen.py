def exists(env):
    return True

def doxygen(env, source):
    docs = env.Command('build/doc/html/index.html', source, 'doxygen doxygen.cfg')
    env.Clean(docs, 'build/doc')
    return env.Dir('build/doc')

def generate(env):
    env.AddMethod(doxygen, 'Doxygen')
