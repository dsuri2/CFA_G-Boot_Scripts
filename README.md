# CFA G-Boot Scripts
Repository of scripts for Cardfight Area, designed for the custom G-Boot &amp; G-EX formats.

## How to use
Place the .exe files in your CFA/texts folder and run them.

If you want you can run the .exe files automatically before running the CFA, I do this using [playnite](https://playnite.link/) scripts, example below:

> Start-Process -FilePath "PATH TO CFA\Text\Clan Changes.exe" -WorkingDirectory "PATH TO CFA\Text"
> 
> Start-Process -FilePath "PATH TO CFA\Text\Remove Banlist.exe" -WorkingDirectory "PATH TO CFA\Text"

## Remove Banlist
This script removes the Premium and Standard banlist from the default clan txt files (does not include the nation files).

## Clan Changes
This script changes the EX files to move the EX cards to be alongside the official cards.

## Why does this exist?
I wanted to make this a repository so that people can see the code if they wanted to run it themselves, or ensure that the code is safe.
