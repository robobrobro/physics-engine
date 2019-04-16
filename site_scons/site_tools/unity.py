from __future__ import print_function
from select import select
from SCons.Builder import Builder
from SCons.Errors import StopError
import os
import subprocess

def exists(env):
    return True

def generate(env, valgrind=False):
    def run_unit_tests(target, source, env):
        runner_path = str(source[0])

        if valgrind:
            cmd = [
                'valgrind',
                '-q',
                '--leak-check=full',
                '--track-origins=yes',
                '--show-leak-kinds=all',
                runner_path,
            ]
        else:
            cmd = [runner_path]

        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        lines = []

        while proc.poll() is None:
            rlist, _, _ = select([proc.stdout, proc.stderr], [], [])
            for r in rlist:
                for line in r.readlines():
                    lines.append(line)
                    print(line, end='')

        if proc.returncode != 0:
            raise StopError('Unit tests failed')

        with open(str(target[0]), 'w') as f:
            f.write(''.join(line for line in lines))

    env['BUILDERS']['RunUnitTests'] = Builder(action=run_unit_tests, single_source=True)

    def build_and_run_unit_tests(env, target, source):
        runner = env.Program('unit_test_runner', source)
        log = env.RunUnitTests(target, runner)
        return log

    env.AddMethod(build_and_run_unit_tests, 'BuildAndRunUnitTests')

    unity_path = os.environ.get('UNITY_PATH')

    if unity_path is None:
        return

    if not os.path.isabs(unity_path):
        unity_path = os.path.join(os.path.abspath(str(env.Dir('#'))), unity_path)

    env['UNITY_PATH'] = unity_path

    env.Append(
        CPPPATH = [
            '$UNITY_PATH/src',
        ],
    )
