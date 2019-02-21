def exists(env):
    return True

def generate(env):
    env.Append(
        LIBS = [
            'dl',
            'GL',
            'm',
            'X11',
            'Xcursor',
            'Xinerama',
            'Xrandr',
            'Xxf86vm',
        ],
        LINKFLAGS = [
            '-pthread',
        ],
    )
