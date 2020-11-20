# D3DXTool

//--------------------------------------------------

Terrain Tool

 Render Option
 
  Solid, WireFrame, Axis pivot
 
 
 Setting
 
  Tile - MaxX, MaxZ, Interval, Detail(UV Tiling)
  
  Transform - Position, Rotation
  
  Texture - TreeController
  

 NavMesh
 
  지형 피킹, 해당 위치에 sphere? 생성, 3개 다 눌렀으면 삼각형 생성
  
  sphere 근처에 다시 눌렀으면 검사해서 같은 위치로 보정해줌
  
  나중에 인덱스 버퍼에 넣어줘야 하는데..?! 당장 어디에 보관?
  

*NavMesh로 카메라도 같이 처리?



//--------------------------------------------------

Mesh Tool

 Render Option
 
  Solid, WireFrame 
  
  
 Object List 
 
  Tree Select in Folder
  
  
 Transform Option 
 
  Scale, Rotation, Position
  
  
 Scene Object List
 
  Static, Dynamic(Update Group), Navi
  
 
*Scene 안에서도 Update할 녀석들을 영역으로 묶어서 관리?


 ex) 계속 상관없이 Update할 것, 특정 상황시에 할 것
 
 
 

//-------------------------------------------------- 

