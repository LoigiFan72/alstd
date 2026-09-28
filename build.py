import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parent
BUILD = ROOT / "build"


def ask_choice(question, choices):
    print()
    print(question)

    for i, choice in enumerate(choices, 1):
        print(f"{i}. {choice}")

    while True:
        try:
            value = int(input("> "))
            if 1 <= value <= len(choices):
                return choices[value - 1]
        except ValueError:
            pass

        print("Invalid choice.")


def main():
    platform = ask_choice(
        "What Platform?",
        ["win", "ctr"]
    )

    debug = ask_choice(
        "Enable Debug?",
        ["yes", "no"]
    )

    debug_printing = ask_choice(
        "Enable Debug Printing?",
        ["yes", "no"]
    )

    build_dir = BUILD / platform

    cmake_args = [
        "cmake",
        "-S", str(ROOT),
        "-B", str(build_dir),
    ]

    if platform == "win":
        cmake_args.append("-DALSTD_PLATFORM_WINDOWS=ON")
    else:
        cmake_args.append("-DALSTD_PLATFORM_CTR=ON")

    if debug == "yes":
        cmake_args.append("-DALSTD_DEBUG=ON")

    if debug_printing == "yes":
        cmake_args.append("-DALSTD_DEBUG_PRINTING=ON")

    print()
    print("Configuring alstd...")
    subprocess.run(cmake_args, cwd=ROOT, check=True)

    print()
    print("Building alstd...")
    subprocess.run(
        ["cmake", "--build", str(build_dir)],
        cwd=ROOT,
        check=True
    )

    print()
    print("Build complete.")


if __name__ == "__main__":
    main()