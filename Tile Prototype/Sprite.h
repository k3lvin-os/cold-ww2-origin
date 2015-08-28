
struct Sprite{

	// Proprieties
	int x, y;
	void *image;
	
	// Functions
	void Show();
	void Move(int changeX, int changeY);
	void GetImage(char name[], int width, int height);	

	// Constructors	
	Sprite(int beginX,int beginY);
	Sprite(char name[], int width, int height,int beginX, int beginY);
	Sprite(char name[], int width, int height);
	Sprite();
		
};

// Show sprite
 void Sprite::Show(){
	putimage(x,y,image,0);
}

// Move sprite
void Sprite::Move(int changeX, int changeY){
	x += changeX;
	y += changeY;
}


// Fill the image variable with the sprite
void Sprite::GetImage(char name[], int width, int height){
	
	readimagefile(name,0,0,width,height); 
	int size = imagesize(0,0,width,height);
	image = malloc(size);
	getimage(0,0,width,height,image); 
}

// Constructor based in a sprite without image, but with coordinates
Sprite::Sprite(int beginX,int beginY){
	x = beginX;
	y = beginY;
}

// Constructor based in a sprite with image and coordinates
Sprite::Sprite(char name[], int width, int height,int beginX, int beginY){
	GetImage(name,width,height);
	x = beginX;
	y = beginY;
}

// Constructor based in a sprite with image, but without a specific coordinate
Sprite::Sprite(char name[], int width, int height){
	GetImage(name,width,height);
}

// Constructor without parameters
Sprite::Sprite(){
	x = 0;
	y = 0;
}


