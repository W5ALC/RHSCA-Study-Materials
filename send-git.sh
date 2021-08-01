#!/bin/bash
echo "# RHSCA-Study-Materials" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/W5ALC/RHSCA-Study-Materials.git
git push -u origin main
