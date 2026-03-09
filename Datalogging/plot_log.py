import matplotlib.pyplot as plt
from pathlib import Path
import re

def plot_log_file(filename):
    """
    Plot data from a log file where each line contains CV, PV, PID, and FAN values.
    Each line is separated by 2 seconds on the time axis.
    """
    # Initialize lists to store data
    times = []
    cv_values = []
    pv_values = []
    pid_values = []
    fan_values = []
    
    # Resolve relative paths from this script folder, not terminal CWD.
    file_path = Path(filename)
    if not file_path.is_absolute():
        file_path = Path(__file__).resolve().parent / file_path

    # Parse the file
    try:
        with open(file_path, 'r') as f:
            lines = f.readlines()
        
        for i, line in enumerate(lines):
            # Parse the line using regex
            cv_match = re.search(r'CV:\s*([\d.]+)', line)
            pv_match = re.search(r'PV:\s*([\d.]+)', line)
            pid_match = re.search(r'PID:\s*([\d.]+)', line)
            fan_match = re.search(r'FAN:\s*([\d.]+)', line)
            
            if cv_match and pv_match and pid_match and fan_match:
                # Extract values
                cv_values.append(float(cv_match.group(1)))
                pv_values.append(float(pv_match.group(1)))
                pid_values.append(float(pid_match.group(1)))
                fan_values.append(float(fan_match.group(1)))
                
                # Calculate time (in seconds, 2 seconds per line)
                time_seconds = i * 2
                times.append(time_seconds)
        
        # Create the plot
        plt.figure(figsize=(12, 6))
        
        plt.plot(times, cv_values, label='CV', linewidth=1)
        plt.plot(times, pv_values, label='PV', linewidth=1)
        plt.plot(times, pid_values, label='PID', linewidth=1)
        plt.plot(times, fan_values, label='FAN', linewidth=1)
        
        plt.xlabel('Time (seconds)', fontsize=12)
        plt.ylabel('Values', fontsize=12)
        plt.title('Humidifier PID', fontsize=14)
        plt.legend(fontsize=10)
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        
        plt.show()
        
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    except Exception as e:
        print(f"Error processing file: {e}")

if __name__ == "__main__":
    # Specify your log file path here
    log_file = "20_1_200"
    plot_log_file(log_file)
