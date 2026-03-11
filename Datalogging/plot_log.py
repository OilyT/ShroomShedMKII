import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from pathlib import Path
import re

LINE_RE = re.compile(
    r"CV:\s*([\d.]+),\s*PV:\s*([\d.]+),\s*PID:\s*([\d.]+),\s*FAN:\s*([\d.]+)"
)


def plot_log_file_live(filename):
    """Live-plot log values and refresh when new lines are appended."""
    times = []
    cv_values = []
    pv_values = []
    pid_values = []
    fan_values = []

    # Resolve relative paths from this script folder, not terminal CWD.
    file_path = Path(filename)
    if not file_path.is_absolute():
        file_path = Path(__file__).resolve().parent / file_path

    try:
        # Open once and keep reading as lines are appended.
        log_file = open(file_path, "r")

        fig, (ax_top, ax_bottom) = plt.subplots(2, 1, figsize=(12, 8), sharex=True)
        (line_cv,) = ax_top.plot([], [], label="CV", linewidth=1)
        (line_pv,) = ax_top.plot([], [], label="PV", linewidth=1)
        (line_pid,) = ax_bottom.plot([], [], label="PID", linewidth=1)
        (line_fan,) = ax_bottom.plot([], [], label="FAN", linewidth=1)

        ax_top.set_title("Humidifier PID (Live)")
        ax_top.set_ylabel("CV / PV")
        ax_top.legend(fontsize=10)
        ax_top.grid(True, alpha=0.3)

        ax_bottom.set_xlabel("Sample")
        ax_bottom.set_ylabel("PID / FAN")
        ax_bottom.legend(fontsize=10)
        ax_bottom.grid(True, alpha=0.3)
        plt.tight_layout()

        def parse_and_append_line(line):
            match = LINE_RE.search(line)
            if not match:
                return

            idx = len(times)
            times.append(idx)
            cv_values.append(float(match.group(1)))
            pv_values.append(float(match.group(2)))
            pid_values.append(float(match.group(3)))
            fan_values.append(float(match.group(4)))

        # Load any existing history first.
        for line in log_file:
            parse_and_append_line(line)

        def update(_frame):
            # Read only newly appended lines since the previous frame.
            new_data = False
            for line in log_file:
                parse_and_append_line(line)
                new_data = True

            if not new_data and not times:
                return line_cv, line_pv, line_pid, line_fan

            line_cv.set_data(times, cv_values)
            line_pv.set_data(times, pv_values)
            line_pid.set_data(times, pid_values)
            line_fan.set_data(times, fan_values)

            if times:
                x_min = 0
                x_max = max(10, len(times) - 1)
                ax_top.set_xlim(x_min, x_max)
                ax_bottom.set_xlim(x_min, x_max)

                top_min = min(cv_values + pv_values)
                top_max = max(cv_values + pv_values)
                if top_min == top_max:
                    top_min -= 1.0
                    top_max += 1.0
                top_pad = (top_max - top_min) * 0.05
                ax_top.set_ylim(top_min - top_pad, top_max + top_pad)

                bottom_min = min(pid_values + fan_values)
                bottom_max = max(pid_values + fan_values)
                if bottom_min == bottom_max:
                    bottom_min -= 1.0
                    bottom_max += 1.0
                bottom_pad = (bottom_max - bottom_min) * 0.05
                ax_bottom.set_ylim(bottom_min - bottom_pad, bottom_max + bottom_pad)

            return line_cv, line_pv, line_pid, line_fan

        anim = FuncAnimation(fig, update, interval=500, blit=False, cache_frame_data=False)
        fig._anim = anim

        try:
            plt.show()
        finally:
            log_file.close()

    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    except Exception as e:
        print(f"Error processing file: {e}")


if __name__ == "__main__":
    # Specify your log file path here
    log_file = "humidifier_pid"
    plot_log_file_live(log_file)
