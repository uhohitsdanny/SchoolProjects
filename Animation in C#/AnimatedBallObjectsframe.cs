//Author: Daniel Navarro
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Timers;

public class Twoobjectsframe : Form
{  private const int formwidth = 1280;  //A graphical area of size 1280x720 has standard aspect ratio 16:9.
   private const int formheight = 720;  //Valid x-coordinates: 0 - 1279; valid y-coordinates: 0-719.
   //In 223n you should use the largest possible graphical area supported by your monitor and still maintain the 16:9 ratio.
   //For 223n projects a graph area of size 1920x1080 looks very nice; even 1600x900 is nice.
   private const int ball_a_radius = 10;
   private const int horizontaladjustment = 8;  //Does anybody have any idea what the purpose of horizontaladjustment is?
   //The next number is the linear distance ball a will move each time its controlling clock tics.  A large number means faster
   //motion and more jerkiness.  A smaller number means less speed but smooth motion.
   private double ball_a_distance_moved_per_refresh = 1.6;  //The unit of measure is 1 pixel.
   private double ball_a_real_coord_x = 1050.0;
    //formheight/2 - ball_a_radius
   private double ball_a_real_coord_y = (double)(70);
   private int ball_a_int_coord_x;  //The x-coordinate of ball a.
   private int ball_a_int_coord_y;  //The y-coordinate of ball a.
   private double ball_a_horizontal_delta;
   private double ball_a_vertical_delta;
   private double ball_a_angle_radians;
   private double save_horizontal;
   private double save_vertical;

   private const double graphicrefreshrate = 30.0;  //30.0 Hz = constant refresh rate during the execution of this animated program.
   private static System.Timers.Timer graphic_area_refresh_clock = new System.Timers.Timer();
   private const double ball_a_update_rate = 30.5;  //Units are Hz
   private static System.Timers.Timer ball_a_control_clock = new System.Timers.Timer();
   private bool ball_a_clock_active = false;  //Initial state: The clock controll ball a is not active.

   private static System.Timers.Timer ball_b_control_clock = new System.Timers.Timer();

   private bool finish = false;
   private bool paused = false;
   private bool reset = false;


   private Pen pen1 = new Pen(Color.Black);
   private SolidBrush brush_for_ball = new SolidBrush(Color.Yellow);
    //Buttons
   private Button go = new Button();
   private Button pause = new Button();
   private Button _exit = new Button();
   private Button _Reset = new Button();
   private Button _OneDirection = new Button();
   private Button _xCoord = new Button();
   private Button _yCoord = new Button();
   private Button _speed = new Button();

   private Point loc_of_go = new Point(1140, 150);
   private Point loc_of_pause = new Point(1140, 150);
   private Point loc_of_reset = new Point(1140, 185);
   private Point loc_of_exit = new Point(1140, 215);
   private Point loc_of_direction = new Point(1140, 270);
   private Point loc_of_speed = new Point(1140, 305);
   private Point loc_of_x = new Point(1115, 500);
   private Point loc_of_y = new Point(1175, 500);
    private TextBox speedbox = new TextBox();


   public Twoobjectsframe()   //The constructor of this class
   {  //Set the title of this form.
       DoubleBuffered = true;
      Text = "Two Animated Balls";
      System.Console.WriteLine("formwidth = {0}. formheight = {1}.",formwidth,formheight);
      //Set the initial size of this form
      Size = new Size(formwidth,formheight);
      //Set the background color of this form
      BackColor = Color.LightGray;
      //Set the initial coordinates of ball a.
      ball_a_int_coord_x = (int)(ball_a_real_coord_x);
      ball_a_int_coord_y = (int)(ball_a_real_coord_y);
      System.Console.WriteLine("Initial coordinates: ball_a_int_coord_x = {0}. ball_a_int_coord_y = {1}.",
                               ball_a_int_coord_x,ball_a_int_coord_y);
      //Instantiate the collection of supporting algorithms
      Twoanimatedlogic algorithms = new Twoanimatedlogic();
      //Set a random angle of direction for ball a: -90.0 degrees <= ball_a_angle <= +90.0 degrees
      ball_a_angle_radians = algorithms.get_random_direction_for_a();
      System.Console.WriteLine("Direction of ball a = {0} degrees",ball_a_angle_radians*180.0/System.Math.PI);
      ball_a_horizontal_delta = ball_a_distance_moved_per_refresh*System.Math.Cos(ball_a_angle_radians);
      ball_a_vertical_delta = ball_a_distance_moved_per_refresh*System.Math.Sin(ball_a_angle_radians);

      graphic_area_refresh_clock.Enabled = false;  //Initially the clock controlling the rate of updating the display is stopped.
      //The next statement tells the clock what method to perform each time the clock makes a tic.
      graphic_area_refresh_clock.Elapsed += new ElapsedEventHandler(Updatedisplay);  

      //Initialize clock of ball a.
      ball_a_control_clock.Enabled = false; //Initially the clock controlling ball a is stopped.
      //The next statement tells the clock what method to perform each time the clock makes a tick.
      ball_a_control_clock.Elapsed += new ElapsedEventHandler(Updateballa);

      Startgraphicclock(graphicrefreshrate);  //refreshrate is how many times per second the display area is re-painted.
      Startballaclock(ball_a_update_rate);    //Set the animation rate for ball a.

       //My code
       //Details of buttons
      /* 
      _speed.Text = ball_a_update_rate.ToString();
      _speed.Location = loc_of_speed;
      _speed.Size = new Size(85, 25);
      _speed.BackColor = Color.Fuchsia;
      
       */
      speedbox.Text = ball_a_update_rate.ToString();
      speedbox.Location = loc_of_speed;
      speedbox.Size = new Size(85, 25);

      _OneDirection.Text = "Down";
      _OneDirection.Location = loc_of_direction;
      _OneDirection.Size = new Size(85, 25);
      _OneDirection.BackColor = Color.Fuchsia;

      _Reset.Text = "Reset";
      _Reset.Location = loc_of_reset;
      _Reset.Size = new Size(85,25);
      _Reset.BackColor = Color.Transparent;

      _exit.Text = "Exit";
      _exit.Location = loc_of_exit;
      _exit.Size = new Size(85, 25);
      _exit.BackColor = Color.Transparent;

      go.Text = "GO";
      go.Location = loc_of_go;
      go.Size = new Size(85, 25);
      go.BackColor = Color.Transparent;

      pause.Text = "PAUSE";
      pause.Location = loc_of_pause;
      pause.Size = go.Size;
      pause.BackColor = Color.Transparent;

      _xCoord.Text = ball_a_int_coord_x.ToString();
      _xCoord.Location = loc_of_x;
      _xCoord.Size = new Size(70, 25);
      _xCoord.BackColor = Color.Transparent;

      _yCoord.Text = ball_a_int_coord_y.ToString();
      _yCoord.Location = loc_of_y;
      _yCoord.Size = new Size(70, 25);
      _yCoord.BackColor = Color.Thistle;




       //Adding controls to screen
      Controls.Add(pause);
      Controls.Add(_Reset);
      Controls.Add(_exit);
      Controls.Add(_OneDirection);
      Controls.Add(speedbox);
      Controls.Add(_xCoord);
      Controls.Add(_yCoord);
   
       //Click events
      go.Click += new EventHandler(go_fn);
      pause.Click += new EventHandler(pause_fn);
      _exit.Click += new EventHandler(exit_fn);
       _Reset.Click += new EventHandler(reset_fn);


   }//End of constructor

   protected override void OnPaint(PaintEventArgs ee)
   {  Graphics graph = ee.Graphics;
      graph.FillEllipse(brush_for_ball,ball_a_int_coord_x,ball_a_int_coord_y,2*ball_a_radius,2*ball_a_radius);
      graph.DrawRectangle(pen1, 100, 80, 960, 560);
      graph.FillRectangle(Brushes.White, 1100, 80, 160, 560);
      //The next statement looks like recursion, but it really is not recursion.
      //In fact, it calls the method with the same name located in the super class.
      base.OnPaint(ee);
   }

   protected void Startgraphicclock(double refreshrate)
   {   double elapsedtimebetweentics;
       if(refreshrate < 1.0) refreshrate = 1.0;  //Avoid dividing by a number close to zero.
       elapsedtimebetweentics = 1000.0/refreshrate;  //elapsedtimebetweentics has units milliseconds.
       //ASK PROF
       graphic_area_refresh_clock.Interval = elapsedtimebetweentics;
       graphic_area_refresh_clock.Enabled = true;  //Start clock ticking.
   }

   protected void Startballaclock(double updaterate)
   {   double elapsedtimebetweenballmoves;
       if(updaterate < 1.0) updaterate = 1.0;  //This program does not allow updates slower than 1 Hz.

       double i = 1;
       if (string.IsNullOrWhiteSpace(speedbox.Text))
       {
           i = ball_a_update_rate;
       }
       else
       {
           Double.TryParse(speedbox.Text, out i);
       }

       elapsedtimebetweenballmoves = 1000.0/i;  //1000.0ms = 1second.  elapsedtimebetweenballmoves has units milliseconds.
       ball_a_control_clock.Interval = elapsedtimebetweenballmoves;
       ball_a_control_clock.Enabled = true;   //Start clock ticking.
       ball_a_clock_active = true;
   }


   protected void Updatedisplay(System.Object sender, ElapsedEventArgs evt)
   {  Invalidate();  //Weird: This creates an artificial event so that the graphic area will repaint itself.
      //System.Console.WriteLine("The clock ticked and the time is {0}", evt.SignalTime);  //Debug statement; remove it later.
      if(!(ball_a_clock_active))
          {graphic_area_refresh_clock.Enabled = false;
           System.Console.WriteLine("The graphical area is no longer refreshing.  You may close the window.");
          }
   }

   protected void Updateballa(System.Object sender, ElapsedEventArgs evt)
   {  
       ball_a_real_coord_x = ball_a_real_coord_x + ball_a_horizontal_delta;
      //In the next statement the minus sign is used because the y-axis is upside down relative to the standard cartesian 
      //coordinate system.
      ball_a_real_coord_y = ball_a_real_coord_y - ball_a_vertical_delta;
  
      ball_a_int_coord_x = (int)System.Math.Round(ball_a_real_coord_x);
      ball_a_int_coord_y = (int)System.Math.Round(ball_a_real_coord_y);

      if (ball_a_int_coord_x == 1050 && ball_a_int_coord_y == 70)
      {
          if (!reset)
          {
              finish = true;
          }
          else
          {
              finish = false;
          }
          _OneDirection.Text = "Down";
          if (finish)
          {
              finish = false;
              ball_a_horizontal_delta = 0;
              ball_a_vertical_delta = -1.0;

              brush_for_ball = new SolidBrush(Color.Gold);
             // Controls.Remove(pause);
              //Controls.Add(go);
              pause_fn2();
          }
          else
          {
              brush_for_ball = new SolidBrush(Color.Yellow);

              go_fn();
          }
      }
      if (ball_a_int_coord_x == 1050 && ball_a_int_coord_y == 630)
      {
          ball_a_vertical_delta = 0.0;
          ball_a_horizontal_delta = -1.0;
          _OneDirection.Text = "Left";
      }
      if (ball_a_int_coord_x == 90 && ball_a_int_coord_y == 630)
      {
          ball_a_vertical_delta = 1.0;
          ball_a_horizontal_delta = 0.0;
          _OneDirection.Text = "Up";
      }
      if (ball_a_int_coord_x == 90 && ball_a_int_coord_y == 70)
      {
          ball_a_vertical_delta = 0.0;
          ball_a_horizontal_delta = 1.0;
          _OneDirection.Text = "Right";
      }

      _xCoord.Text = ball_a_int_coord_x.ToString();
      _yCoord.Text = ball_a_int_coord_y.ToString();

      //System.Console.WriteLine("The clock ticked for ball a and the time is {0}", evt.SignalTime);//Debug statement; remove later.
      //Determine if ball a has passed beyond the graphic area.
      if(ball_a_int_coord_x >= formwidth || ball_a_int_coord_y + 2*ball_a_radius <= 0 || ball_a_int_coord_y >= formheight)
          {ball_a_clock_active = false;
           ball_a_control_clock.Enabled = false;
           System.Console.WriteLine("The clock controlling ball a has stopped.");
          }
   }//End of method Updateballa

   protected void go_fn(Object sender, EventArgs events)
   {
      paused = false;
       brush_for_ball = new SolidBrush(Color.Yellow);
       ball_a_horizontal_delta = save_horizontal;
       ball_a_vertical_delta = save_vertical;
       Controls.Remove(go);
       Controls.Add(pause);
       Startballaclock(ball_a_update_rate);
   }
   protected void go_fn()
   {
       paused = false;
       brush_for_ball = new SolidBrush(Color.Yellow);
       ball_a_horizontal_delta = save_horizontal;
       ball_a_vertical_delta = save_vertical;
       Controls.Remove(go);
       Controls.Add(pause);
       Startballaclock(ball_a_update_rate);
   }
   protected void pause_fn(Object sender, EventArgs events)
   {
       paused = true;
       save_horizontal = ball_a_horizontal_delta;
       save_vertical = ball_a_vertical_delta;
       ball_a_horizontal_delta = 0;
       ball_a_vertical_delta = 0; 
       Controls.Add(go);
       Controls.Remove(pause);
   }
   protected void pause_fn2()
   {
       paused = true;
       save_horizontal = ball_a_horizontal_delta;
       save_vertical = ball_a_vertical_delta;
       ball_a_horizontal_delta = 0;
       ball_a_vertical_delta = 0;
       Controls.Add(go);
       Controls.Remove(pause);
   }
   protected void exit_fn(Object sender, EventArgs events)
   {
       Close();
   }
   protected void reset_fn(Object sender, EventArgs events)
   {
       ball_a_real_coord_x = 1050;
       ball_a_real_coord_y = 70;
       if (paused)
       {
           ball_a_vertical_delta = -1.0;
           ball_a_horizontal_delta = 0.0;
           pause_fn2();
           _OneDirection.Text = "Down";
           reset = true;

       }
       else
       {
           save_vertical = -1.0;
           save_horizontal = 0.0;
           ball_a_vertical_delta = -1.0;
           ball_a_horizontal_delta = 0.0;
           _OneDirection.Text = "Down";
           reset = true;
       }
   }



}//End of class Twoobjectsframe



