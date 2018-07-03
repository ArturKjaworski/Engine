"Game" class - main game class: 
	- has game objects (player, pickupObjects)
	- collision callback
	- creating world (physX world and rendering meshes)
 
Player folder:
	*Camera class:
		- player's camera (movement, rotation, zoom in/out)
	*Player class:
		- player fields (e.g. hp, ammmo, camera object)
		- player movement/interaction
		- is holding hitBox(PhysX actor)

Objects folder:
	* Interactable_Obj:
		- root class
		- has general purpose functions and fields
	* PickUp_Obj
		- derived from Interactable_Obj
		- has functions for picking up objects
	* Coin
		- derived from PickUp_Obj
		- final class for Coins (Ammo in that case)

labirynth gen:
	*LabGen class:
		-generating maze
		- has Labfield class objects
	*Labfield class:
		- has position
		- control its own walls
		
graphics classes folder:
	Targa:
		- open .tga texture format for usage in app
	ThreeMaxLoader:
		- open .3ds model format for usage in app

"Vec3" Class:
	- create (x,y,z) vector
	- has few overloaded operators
	- can normalize 
