import math
import subprocess
from pathlib import Path

def euclidean(v1, v2):
    return math.sqrt(sum((a - b) ** 2 for a, b in zip(v1, v2)))

def dtw_distance(series_a, series_b):
    n = len(series_a)
    m = len(series_b)
    dp = [[float("inf")] * (m + 1) for _ in range(n + 1)]
    dp[0][0] = 0.0
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            cost = euclidean(series_a[i - 1], series_b[j - 1])
            dp[i][j] = cost + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
    return dp[n][m]

def build_cpp_binary(root: Path) -> Path:
    binary = root / "build_test_multid"
    sources = [
        "tests/test_multid.cpp",
        "FastDTW-x/Classes/ColMajorCell.cpp",
        "FastDTW-x/Classes/FastDTW.cpp",
        "FastDTW-x/Classes/SearchWindow.cpp",
        "FastDTW-x/Classes/WarpPath.cpp",
    ]
    cmd = ["g++", "-std=c++17", "-I."] + sources + ["-o", str(binary)]
    subprocess.run(cmd, check=True, cwd=root)
    return binary


def main():
    series_a = [(0.0, 1.0), (1.0, 2.0), (2.0, 3.0), (3.0, 4.5)]
    series_b = [(0.0, 1.2), (1.2, 2.1), (2.0, 3.2), (3.5, 4.8)]

    python_dtw = dtw_distance(series_a, series_b)
    print(f"python_dtw_distance={python_dtw:.5f}")

    root = Path(__file__).resolve().parents[1]
    binary = build_cpp_binary(root)
    try:
        proc = subprocess.run([str(binary)], check=True, capture_output=True, text=True, cwd=root)
        print(proc.stdout.strip())
    finally:
        if binary.exists():
            binary.unlink()


if __name__ == "__main__":
    main()
