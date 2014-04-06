import sys
import drive
try:
  import wpilib
except ImportError:
  from pyfrc import wpilib
DriveStick = wpilib.Joystick(1)
ShootStick = wpilib.Joystick(2)
leftMotor = wpilib.Jaguar(1)
compressor = wpilib.Compressor(2,1)
def restartCode():
  if stick.GetRawButton(2):
    raise RuntimeError("restarting")
# Contains the Disabled, Auto, and Teleop functions
class Zaphod(wpilib.SimpleRobot):
  def Disabled(self):
    while self.IsDisabled():
      wpilib.Wait(0.01)
  def Autonomous(self):
    self.GetWatchdog().SetEnabled(False)
    while self.IsAutonomous() and self.IsEnabled():
      wpilib.Wait(0.01)
  def OperatorControl(self):
    # Create the watchdog (and actually use it)
    dog = self.GetWatchdog()
    dog.SetEnabled(True)
    dog.SetExpiration(0.25)
    compressor.Start()
    while self.IsOperatorControl() and self.IsEnabled():
      dog.Feed()
      leftMotor.Set(DriveStick.GetY())
      wpilib.Wait(0.04)
def run():
  robot = Zaphod()
  robot.StartCompetition()
  return robot
