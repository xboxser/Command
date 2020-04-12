
#include <iostream>
#include <string>
using namespace std;

class Light
{
	string descr;
public:
	Light(string d) { descr = d; }
	void on() { cout << descr << ": Light is on" << endl; }
	void off() { cout << descr << ": Light is off" << endl; }
};

class GarageDoor
{
public:
	void up() { cout << "Garage door is open" << endl; }
	void down() { cout << "Garage door is close" << endl; }
};

class Stereo
{
public:
	void on() { cout << "Stereo is on" << endl; }
	void off() { cout << "Stereo is off" << endl; }
	void setCd() { cout << "Stereo is set for CD input" << endl; }
	void setDvd() { cout << "Stereo is set for DVD input" << endl; }
	void setRadio() { cout << "Stereo is set for radio" << endl; }
	void setVolume(int v) { cout << "Stereo volume set to " << v << endl; }
};

class Command
{
public:
	virtual void execute() = 0;
};

class NoCommand : public Command
{
public:
	virtual void execute() {}
};

class LightOnCommand : public Command
{
	Light* light;
public:
	LightOnCommand(Light* l) { light = l; }
	virtual void execute() { light->on(); }
};
class LightOffCommand : public Command
{
	Light* light;
public:
	LightOffCommand(Light* l) { light = l; }
	virtual void execute() { light->off(); }
};

class GarageDoorUpCommand : public Command
{
	GarageDoor* garageDoor;
public:
	GarageDoorUpCommand(GarageDoor* gd) { garageDoor = gd; }
	virtual void execute() { garageDoor->up(); }
};
class GarageDoorDownCommand : public Command
{
	GarageDoor* garageDoor;
public:
	GarageDoorDownCommand(GarageDoor* gd) { garageDoor = gd; }
	virtual void execute() { garageDoor->down(); }
};

class StereoOnWithCDCommand : public Command
{
	Stereo* stereo;
public:
	StereoOnWithCDCommand(Stereo* s) { stereo = s; }
	virtual void execute()
	{
		stereo->on();
		stereo->setCd();
		stereo->setVolume(11);
	}
};
class StereoOffCommand : public Command
{
	Stereo* stereo;
public:
	StereoOffCommand(Stereo* s) { stereo = s; }
	virtual void execute() { stereo->off(); }
};

//Пульт
class RemoteControl
{
	int countButtons;
	Command** onCommands;
	Command** offCommands;
	NoCommand* noCommand;
public:
	RemoteControl(int c)
	{
		countButtons = c;
		onCommands = new Command * [c];
		offCommands = new Command * [c];
		noCommand = new NoCommand;
		for (int i = 0; i < c; i++)
		{
			onCommands[i] = noCommand;
			offCommands[i] = noCommand;
		}
	}
	~RemoteControl()
	{
		delete[]onCommands;
		delete[]offCommands;
		delete noCommand;
	}
	void setCommand(int slot, Command* onCommand, Command* offCommand)
	{
		if (onCommands[slot] != noCommand) delete onCommands[slot];
		onCommands[slot] = onCommand;
		if (offCommands[slot] != noCommand) delete offCommands[slot];
		offCommands[slot] = offCommand;
	}
	void onButtonWasPushed(int slot) { onCommands[slot]->execute(); }
	void offButtonWasPushed(int slot) { offCommands[slot]->execute(); }
};

int main()
{
	RemoteControl rc(7);
	Light* livingRoomLight = new Light("Living Room");
	Light* kitchenLight = new Light("Kitchen");
	GarageDoor* garageDoor = new GarageDoor;
	Stereo* stereo = new Stereo;

	LightOnCommand* livingRoomLightOn = new LightOnCommand(livingRoomLight);
	LightOffCommand* livingRoomLightOff = new LightOffCommand(livingRoomLight);
	LightOnCommand* kitchenLightOn = new LightOnCommand(kitchenLight);
	LightOffCommand* kitchenLightOff = new LightOffCommand(kitchenLight);
	GarageDoorUpCommand* garageDoorUp = new GarageDoorUpCommand(garageDoor);
	GarageDoorDownCommand* garageDoorDown = new GarageDoorDownCommand(garageDoor);
	StereoOnWithCDCommand* stereoOnWithCD = new StereoOnWithCDCommand(stereo);
	StereoOffCommand* stereoOff = new StereoOffCommand(stereo);

	rc.setCommand(0, livingRoomLightOn, livingRoomLightOff);
	rc.setCommand(1, kitchenLightOn, kitchenLightOff);
	rc.setCommand(2, garageDoorUp, garageDoorDown);
	rc.setCommand(3, stereoOnWithCD, stereoOff);

	for (int i = 0; i < 7; i++)
	{
		rc.onButtonWasPushed(i);
		rc.offButtonWasPushed(i);
	}
	return 0;
}
