#!/usr/bin/env python3

import argparse

import matplotlib.pyplot as plt
import pandas as pd


def plot_trajectory(input_file, output_file, moon_scale_factor):

    df = pd.read_csv(input_file)

    # scale Moon's trajectory for better visibility
    df["moon_trajectory_scaled_x"] = df["earth_x"] + (df["moon_x"] - df["earth_x"]) * moon_scale_factor
    df["moon_trajectory_scaled_y"] = df["earth_y"] + (df["moon_y"] - df["earth_y"]) * moon_scale_factor

    # plotting
    plt.figure(figsize=(10, 10))
    plt.plot(df["earth_x"], df["earth_y"], label="Earth", color="green")
    plt.plot(df["moon_trajectory_scaled_x"], df["moon_trajectory_scaled_y"], label="Moon", color="gray")
    plt.plot(0, 0, 'o', label="Sun", color="red") # a point

    # props
    plt.title(f"Moon trajectory around the Earth, around the Sun. Moon scaling = {moon_scale_factor}x")
    plt.xlabel("X-Pos [m]")
    plt.ylabel("Y-Pos [m]")
    plt.grid(True)
    plt.axis("equal")

    plt.legend()

    # save output
    plt.savefig(output_file)
    print(f"Result saved to {output_file}!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Plot the trajectory of the Moon relative to the Sun.")
    parser.add_argument('-i', "--input-file", default="../output.csv", help="Path to the input CSV file containing trajectory data.")
    parser.add_argument('-o', "--output-file", default="./output.png", help="Path to the output PNG file to save the plot.")
    parser.add_argument('-s', "--scale-moon", type=float, default=20, help="Scale factor for the Moon's trajectory.")
    args = parser.parse_args()

    if args.scale != 20:
        print(f"Using moon scale factor: {args.scale}")

    plot_trajectory(args.input_file, args.output_file, args.scale)



