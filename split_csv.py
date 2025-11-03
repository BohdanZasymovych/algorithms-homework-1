import csv
import random
import os
import sys

def create_random_csv_samples(input_csv_path, output_dir):
    # Read all rows from original CSV
    with open(input_csv_path, newline='', encoding='utf-8') as f:
        reader = csv.reader(f)
        header = next(reader)
        rows = list(reader)

    total_entities = len(rows)

    # Check if we have enough rows
    if total_entities < 10000:
        raise ValueError("The original CSV has fewer than 10,000 rows, cannot create required samples.")

    # Sizes for new CSVs
    sizes = [10000 * i for i in range(1, 11)]  # 10k, 20k, ..., 100k

    for size in sizes:
        if size > total_entities:
            raise ValueError(f"Not enough rows to create file with {size} entities.")

        sampled_rows = random.sample(rows, size)
        output_path = os.path.join(output_dir, f"sample_{size}.csv")

        with open(output_path, 'w', newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(header)
            writer.writerows(sampled_rows)

        print(f"Created {output_path} with {size} rows.")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python create_csv_samples.py <input_csv_path> <output_directory>")
        sys.exit(1)

    input_csv = sys.argv[1]
    output_dir = sys.argv[2]

    if not os.path.exists(output_dir):
        print(f"Directory {output_dir} does not exist.")
        sys.exit(1)

    if os.listdir(output_dir):
        print(f"Directory {output_dir} is not empty. Please provide an empty directory.")
        sys.exit(1)

    create_random_csv_samples(input_csv, output_dir)
