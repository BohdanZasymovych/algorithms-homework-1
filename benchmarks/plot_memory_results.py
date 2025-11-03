import os
import pandas as pd
import matplotlib.pyplot as plt
import re

def plot_memory_csv_results(folder_path, output_path):
    """
    Reads CSV files in the given folder, extracts class names from file names,
    sorts data by 'Size', plots 'Size' vs 'MemoryBytes' for each class,
    and saves the plot.

    Args:
        folder_path (str): Folder containing CSV files.
        output_path (str): File path to save the plot image.
    """
    if not os.path.isdir(folder_path):
        raise FileNotFoundError(f"Folder not found: {folder_path}")

    csv_files = [f for f in os.listdir(folder_path) if f.endswith('.csv')]
    if len(csv_files) < 1:
        raise FileNotFoundError("No CSV files found in the folder.")

    plt.figure(figsize=(10, 6))

    for csv_file in csv_files:
        file_path = os.path.join(folder_path, csv_file)
        df = pd.read_csv(file_path)

        if 'Size' not in df.columns or 'MemoryBytes' not in df.columns:
            raise ValueError(f"CSV file {csv_file} must have columns 'Size' and 'MemoryBytes'.")

        # Sort by Size
        df = df.sort_values(by='Size')

        # Extract full class name from file name: e.g. "12StudentBase1_results.csv" -> "StudentBase1"
        base_name = os.path.splitext(csv_file)[0]  # Remove .csv
        class_name = re.sub(r'^\d+', '', base_name).split('_results')[0]

        plt.plot(df['Size'], df['MemoryBytes'], marker='o', label=class_name)

    plt.xlabel('Size')
    plt.ylabel('Memory (Bytes)')
    plt.title('Memory Usage Comparison of Classes')
    plt.legend()
    plt.grid(True)

    plt.savefig(output_path)
    plt.close()
    print(f"Plot saved to {output_path}")


# Example usage
if __name__ == "__main__":
    folder = "/home/bohdan/code/algorithms/homework-1/benchmarks/benchmark-results/memory"
    output = "/home/bohdan/code/algorithms/homework-1/benchmarks/benchmark-plots/plot_memory.png"
    plot_memory_csv_results(folder, output)
