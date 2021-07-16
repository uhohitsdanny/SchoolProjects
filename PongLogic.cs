//Author: Daniel Navarro

public class Oneanimatedlogic
{  
            private System.Random randomgenerator = new System.Random();

    public double get_starting_direction_for_a()
       {
            double randomnum = randomgenerator.NextDouble();
            double startingnumber = 0.0;
            startingnumber = startingnumber - randomnum;
            double ball_a_angle_radians = System.Math.PI * startingnumber;
            return ball_a_angle_radians;
       }

}
