# cub3D

**A first-person 3D maze explorer built with raycasting.**

This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever.

**Key Features:**

* **Realistic 3D Rendering:** Experience 3D graphics powered by raycasting.
* **Parse:** Experience 3D graphics powered by raycasting.
* **Maps:** Design your own unique mazes with various wall textures and layouts.
* **First-Person Perspective:** Navigate freely through the maze, controlling your movement and view.

## Under the Hood:
* **C Programming:** The core of the project is built using C programming language.
* **miniLibX Library:** This project was built upon the minilibx-linux library, a custom version provided by Ecole 42.
* **Raycasting Algorithm:** The heart of the project, enabling real-time 3D rendering from a 2D map.


### Map Parsing
   - File Reading and Validation:
     - Function to open and read only the .cub file.
     - Ensure the file is properly closed after reading.
     - Implement basic error handling (e.g., invalid file format).
   
   - Texture Parsing:
     - Handle parsing of texture paths for walls and other surfaces.
     - Validate that each texture file exists and can be loaded.
       
   - Map Boundary Validation:
     - Ensure that the map is properly surrounded by walls (1).
     - Handle edge cases for maps with varying dimensions.
     - Function that converts the map layout into a usable format for the game.

   - Player Initialization:
     - Parse the player's initial position and orientation (N, S, E, W).
     - Validate the map contains exactly one player start position.
   

### Raycasting
   - Basic Raycasting Algorithm:
     - Implement the core raycasting loop to calculate the distance to walls.
     - Handle ray direction and casting for different player orientations (North, South, 
	 East, West).
   
   - Projection and Rendering:
     - Convert raycasting data into a 2D projection on the screen.
     - Implement drawing of the vertical slices on the screen.
   
   - DDA Algorithm and Wall Detection:
     - Implement the Digital Differential Analyzer (DDA) algorithm to determine when a ray 
	 hits a wall.
     - Handle both horizontal and vertical wall detection.
   
   - Field of View and Camera Movement:
     - Set up the player's field of view (FOV) and adjust the raycasting to reflect this.
     - Implement smooth rotation (left and right) and forward/backward movement.

   - Collision Detection:
     - Integrate collision detection into player movement so that the player cannot walk 
	 through walls.
     - Handle edge cases, such as diagonal movement into walls.


## Getting Started:

1. Clone the Repository:
   ``
   git clone https://github.com/Lucas42Porto/42_cub3d.git
  ``

2. Build:
   ``
    make
  ``
  
3. **Run:**
   ``
   ./cub3D <dir/map_file.cub>
  ``
4. **Example:**
   ``
   ./cub3D maps/maps/challenges/prova.cub
  ``
## Controls

You can move around the maze with ``W`` ``A`` ``S`` ``D``.

You can also rotate the view with the directional arrows ``←`` and ``→``.

To exit the game, press ``ESC`` or click the red cross.
  
