try:
  import wpilib
except ImportError:
  from pyfrc import wpilib
class drive():
  def _init_(self, rightBack, rightMid, rightFront, leftBack, leftMid, leftFront):
