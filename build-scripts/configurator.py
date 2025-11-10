from pathlib import Path
import subprocess

def configure_cmake(cmake_vars: dict, build: bool = False):
    source_dir = Path(__file__).parents[1]
    build_dir = source_dir / "build"

    # Configure
    command = ["cmake"]
    command.append("-S" + str(source_dir.absolute()))
    command.append("-B" + str(build_dir.absolute()))

    for (key, value) in zip(cmake_vars.keys(), cmake_vars.values()):
        if key is None:
            raise Exception("Key cannot be None")
        if value is None:
            command.append(f"-D{key}")
        else:
            command.append(f"-D{key}={value}")

    subprocess.run(command)

    # Build
    if build:
        subprocess.run(['cmake', '--build', build_dir])