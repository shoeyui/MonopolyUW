main : AcademicBuilding.o Block.o Game.o Gym.o main.o MyInfoBoard.o NonProperty.o Player.o Property.o Residence.o RurCup.o
	g++ AcademicBuilding.o Block.o Game.o Gym.o main.o MyInfoBoard.o NonProperty.o Player.o Property.o Residence.o RurCup.o -o bb7k
AcademicBuilding.o : AcademicBuilding.h AcademicBuilding.cc Property.h
	g++ -c AcademicBuilding.cc
Block.o : Block.h Block.cc Player.h MyInfoBoard.h
	g++ -c Block.cc
Game.o : Game.h Game.cc Block.h Player.h NonProperty.h AcademicBuilding.h Residence.h Gym.h MyInfoBoard.h
	g++ -c Game.cc
Gym.o : Gym.h Gym.cc Property.h
	g++ -c Gym.cc
main.o : main.cc Game.h
	g++ -c main.cc
MyInfoBoard.o : MyInfoBoard.h MyInfoBoard.cc
	g++ -c MyInfoBoard.cc
NonProperty.o : NonProperty.h NonProperty.cc Block.h Player.h
	g++ -c NonProperty.cc
Player.o : Player.h Player.cc Property.h RurCup.h
	g++ -c Player.cc
Property.o : Property.h Property.cc Block.h Player.h
	g++ -c Property.cc
Residence.o : Residence.h Residence.cc Residence.h
	g++ -c Residence.cc
RurCup.o :: RurCup.h RurCup.cc
	g++ -c RurCup.cc
