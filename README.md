# LineDrawer
Quick and easy editor for drawing lines into a CSV file ✏️📁

https://github.com/user-attachments/assets/99be9a72-24e3-4434-b325-3fda3f8e20cd

# Why Did I Make This? 💭
Another project of mine, [AudioTracer](https://github.com/Clafted/AudioTracer), depended on files containing line-data. Initially, these files were manually typed, which easily becomes an inconvenience as complex designs are made. To combat this issue then, LineDrawer was made!

# Experience Gained in Development 🧠
This is my second graphics editor, following [Tick-Rate-Map-Maker](https://github.com/Clafted/Tick-Rate-Map-Maker), so I figured developing LineDrawer would be simple. I was wrong. There's a difference between TRMM and LineDrawer, and its that the former is a *raster* graphics editor, and LineDrawer is a *vector* graphics editor. From my experience, vector graphics easily grow more complex in its continuous nature, as opposed to raster graphics' more discrete use of grids; vector graphics concerns the manipulation of entire shapes, whereas raster graphics only concerns squares in a grid. It's the difference between drawing on a blank canvas and filling in the blanks on a form: one has more range.
## Technical Value
- Developed flexible Action system which allows for the re/undoing of move, erase, and draw Actions
- Designed and Implemented GUI framework to support numerous GUI layers
- Implemented filesystem setup/access to identify and list valid line files
