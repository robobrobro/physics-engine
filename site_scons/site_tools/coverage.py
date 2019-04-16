def exists(env):
    return True

def generate(env):
    env.Append(
        CCFLAGS = '--coverage',
        LINKFLAGS = '--coverage',
    )

    def generate_coverage(env, target, source, data_dir=None, base_dir=None, title=None, prefix=None):
        action = 'lcov -c -o $TARGET'

        if data_dir is not None:
            action += ' -d {}'.format(env.Dir(data_dir))

        if base_dir is not None:
            action += ' -b {}'.format(env.Dir(base_dir))

        cov_info = env.Command('cov.info', source, action)

        action = 'genhtml --legend --function-coverage --branch-coverage -o $TARGET $SOURCE'

        if title is not None:
            action += ' -t {}'.format(title)

        if prefix is not None:
            action += ' -p {}'.format(prefix)

        html_dir = env.Command(target, cov_info, action)

        return html_dir

    env.AddMethod(generate_coverage, 'GenerateCodeCoverageReport')
