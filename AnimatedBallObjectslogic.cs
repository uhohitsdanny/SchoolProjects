//Author: Daniel Navarro

public class Twoanimatedlogic
{   private System.Random randomgenerator = new System.Random();

    public double get_random_direction_for_a()
       {//This method returns a random angle in radians in the range: -π/2 <= angle <= +π/2
           double randomnumber = -90.0;//randomgenerator.NextDouble();
        randomnumber = randomnumber - 0.5;
        double ball_a_angle_radians = System.Math.PI * randomnumber;
        return ball_a_angle_radians;
       }//End of computefibonaccinumber

}//End of Twoanimatedlogic
