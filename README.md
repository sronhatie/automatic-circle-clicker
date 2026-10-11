# Automatic Circle Clicker

A program that clicks circles for you whenever you hover over the circle (a.k.a. relax mod). Written in C and x64 assembly.

This is a personal project, not intended for public use, hence why there's only the source code and no binary or a guide to make it run.

If you do end up using it, use it at your own risk.

## Features

- Automatic clicking for circles when the cursor is hovering over them
- Automatic holding for sliders (SPINNERS NOT INCLUDED *yet*)
- Selection of the earliest eligible hit object
- External process memory reading
- Pattern scanning and a temporary x64 inline hook

## How it works

Uses Windows API to interact with the osu! process.

The program reads osu!lazer's internal gameplay state to figure out which hit objects are active and when they should be hit.

It basically uses the same method that the real game uses for its relax logic. [osu!lazer implementation of relax](https://github.com/ppy/osu/blob/master/osu.Game.Rulesets.Osu/Mods/OsuModRelax.cs)

Uses an external inline hook to obtain an internal game object pointer, then follows memory offsets to access gameplay information.

## Future plans

- Make it stable? It technically works, but so many things could go wrong. Bad code.
- Make a pretty UI. Will probably hand draw it and use Direct2D
