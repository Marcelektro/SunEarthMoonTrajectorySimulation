#!/usr/bin/env python3

import argparse
import os

import matplotlib.pyplot as plt
import pandas as pd


def plot_trajectory(input_file, output_file):

    df = pd.read_csv(input_file)

    # scale Moon's trajectory for better visibility
    scale = 37
    df["moon_trajectory_scaled_x"] = df["earth_x"] + (df["moon_x"] - df["earth_x"]) * scale
    df["moon_trajectory_scaled_y"] = df["earth_y"] + (df["moon_y"] - df["earth_y"]) * scale

    # plotting
    plt.figure(figsize=(10, 10))
    plt.plot(df["earth_x"], df["earth_y"], label="Earth", color="green")
    plt.plot(df["moon_trajectory_scaled_x"], df["moon_trajectory_scaled_y"], label="Moon", color="gray")
    plt.plot(0, 0, 'o', label="Sun", color="red") # a point

    # props
    plt.title(f"Moon trajectory around the Earth, around the Sun. Moon scaling = {scale}x")
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
    args = parser.parse_args()

    plot_trajectory(args.input_file, args.output_file)



