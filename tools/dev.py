"""Build and run the C++ engine using tools installed by uv."""

import argparse
from pathlib import Path
import shutil
import subprocess
import sys


ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("build", "run"))
    parser.add_argument("--config", choices=("Debug", "Release"), default="Debug")
    args = parser.parse_args()

    cmake = shutil.which("cmake")
    ninja = shutil.which("ninja")
    if cmake is None or ninja is None:
        parser.exit(1, "Missing CMake or Ninja. Run uv sync, then use uv run.\n")

    build_dir = ROOT / "build" / args.config.lower()
    try:
        subprocess.run(
            [
                cmake, "-S", str(ROOT), "-B", str(build_dir), "-G", "Ninja",
                f"-DCMAKE_BUILD_TYPE={args.config}",
                f"-DCMAKE_MAKE_PROGRAM={ninja}",
                "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
            ],
            cwd=ROOT,
            check=True,
        )
        subprocess.run([cmake, "--build", str(build_dir)], cwd=ROOT, check=True)

        if args.action == "run":
            executable = build_dir / ("warriors.exe" if sys.platform == "win32" else "warriors")
            subprocess.run([str(executable)], cwd=ROOT, check=True)
    except subprocess.CalledProcessError as error:
        return error.returncode if error.returncode > 0 else 1
    except OSError as error:
        print(f"Could not execute build tool or engine: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
