//Author: Daniel Navarro
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Timers;

public class Oneobjectsframe : Form
{  private const int formwidth = 1280;  //A graphical area of size 1280x720 has standard aspect ratio 16:9.
   private const int formheight = 720;  //Valid x-coordinates: 0 - 1279; valid y-coordinates: 0-719.
   private const int ball_a_radius = 10;
   private double ball_a_distance_moved_per_refresh = 1.6;  //The unit of measure is 1 pixel.
   private double ball_a_real_coord_x = 550.0;
   private double ball_a_real_coord_y = (double)(350);
   private int ball_a_int_coord_x = 0;
   private int ball_a_int_coord_y = 0;
   private double ball_a_horizontal_delta;
   private double ball_a_vertical_delta;
   private double radians = 0.0;
   private int degrees = 0;
   private bool start_active = false;

   private const double graphicrefreshrate = 30.0;  //30.0 z = constant refresh rate during the execution of this animated program.
   private static System.Timers.Timer graphic_area_refresh_clock = new System.Timers.Timer();
   private const double ball_a_update_rate = 30.0;  //Units are Hz
   private static System.Timers.Timer ball_a_control_clock = new System.Timers.Timer();
   private bool ball_a_clock_active = false;  //Initial state: The clock controll ball a is not active.
   private static System.Timers.Timer ball_b_control_clock = new System.Timers.Timer();
                
   private Pen pen1 = new Pen(Color.Black);
   private SolidBrush brush_for_ball = new SolidBrush(Color.Navy);
    //Buttons
   private Button title = new Button();
   private Button start = new Button();
   private Button pause = new Button();
   private Button _exit = new Button();
   private Button _Reset = new Button();
   private Button _xCoord = new Button();
   private Button _yCoord = new Button();
   private Button _speed = new Button();

   private Point loc_of_start = new Point(1140, 150);
   private Point loc_of_pause = new Point(1140, 150);
   private Point loc_of_reset = new Point(1140, 185);
   private Point loc_of_exit = new Point(1140, 215);
   private Point loc_of_direction = new Point(1140, 270);
   private Point loc_of_speed = new Point(1140, 305);
   private Point loc_of_refreshrate = new Point(1140, 325);
   private Point loc_of_x = new Point(1115, 500);
   private Point loc_of_y = new Point(1175, 500);
   private TextBox speedbox = new TextBox();
   private TextBox graphicrefresh = new TextBox();
   private TextBox _OneDirection = new TextBox();


   public Oneobjectsframe()   //The constructor of this class
   {  //Set the title of this form.
       DoubleBuffered = true;
      Text = "Ricochet Ball";
      System.Console.WriteLine("formwidth = {0}. formheight = {1}.",formwidth,formheight);
      Size = new Size(formwidth,formheight);
      BackColor = Color.LightGray;
      //Set the initial coordinates of ball a.
      ball_a_int_coord_x = (int)(ball_a_real_coord_x);
      ball_a_int_coord_y = (int)(ball_a_real_coord_y);
      System.Console.WriteLine("Initial coordinates: ball_a_int_coord_x = {0}. ball_a_int_coord_y = {1}.",
                               ball_a_int_coord_x,ball_a_int_coord_y);

      graphic_area_refresh_clock.Enabled = false;  //Initially the clock controlling the rate of updating the display is stopped.
      //The next statement tells the clock what method to perform each time the clock makes a tic.
      graphic_area_refresh_clock.Elapsed += new ElapsedEventHandler(Updatedisplay);  

      //Initialize clock of ball a.
      ball_a_control_clock.Enabled = false; //Initially the clock controlling ball a is stopped.
      //The next statement tells the clock what method to perform each time the clock makes a tick.
      ball_a_control_clock.Elapsed += new ElapsedEventHandler(Updateballa);

      Startgraphicclock(graphicrefreshrate);
      Startballaclock(ball_a_update_rate);    //Set the animation rate for ball a.

      title.Text = "Ricochet Ball by Daniel Navarro";
      title.Location = new Point(540, 10);
      title.Size = new Size(185, 20);
      title.BackColor = Color.AntiqueWhite;

      speedbox.Text = ball_a_update_rate.ToString();
      speedbox.Location = loc_of_speed;
      speedbox.Size = new Size(85, 25);

      graphicrefresh.Text = graphicrefreshrate.ToString();
      graphicrefresh.Location = loc_of_refreshrate;
      graphicrefresh.Size = new Size(85, 25);

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

      start.Text = "Start";
      start.Location = loc_of_start;
      start.Size = new Size(85, 25);
      start.BackColor = Color.Transparent;

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
      Controls.Add(graphicrefresh);
      Controls.Add(_xCoord);
      Controls.Add(_yCoord);
      Controls.Add(title);
       //Click events
      start.Click += new EventHandler(start_fn);
      _exit.Click += new EventHandler(exit_fn);
       _Reset.Click += new EventHandler(reset_fn);
   }
   protected override void OnPaint(PaintEventArgs ee)
   {  Graphics graph = ee.Graphics;
      graph.FillEllipse(brush_for_ball,ball_a_int_coord_x,ball_a_int_coord_y,2*ball_a_radius,2*ball_a_radius);
      graph.DrawRectangle(pen1, 100, 80, 960, 560);
      graph.FillRectangle(Brushes.White, 1100, 80, 160, 560);
      graph.FillRectangle(Brushes.White, 0,0, 1280, 65);
      base.OnPaint(ee);
   }
   protected void Startgraphicclock(double refreshrate)
   {   double elapsedtimebetweentics;
       if(refreshrate < 1.0) refreshrate = 1.0;

       double j;
       Double.TryParse(graphicrefresh.Text, out j);

       elapsedtimebetweentics = 1000.0/j;  //elapsedtimebetweentics has units milliseconds.
       graphic_area_refresh_clock.Interval = elapsedtimebetweentics;
       graphic_area_refresh_clock.Enabled = true;  //Start clock ticking.
   }
   protected void Startballaclock(double updaterate)
   {   
       double elapsedtimebetweenballmoves;
       double i;
       double j;
       Double.TryParse(_OneDirection.Text, out j);
       ball_a_horizontal_delta = ball_a_distance_moved_per_refresh * System.Math.Cos(j * System.Math.PI / 180.0);
       ball_a_vertical_delta = ball_a_distance_moved_per_refresh * System.Math.Sin(j * System.Math.PI / 180.0);

       if(updaterate < 1.0) updaterate = 1.0;  //This program does not allow updates slower than 1 Hz.
       Double.TryParse(speedbox.Text, out i);
       elapsedtimebetweenballmoves = 1000.0/i;  //1000.0ms = 1second.  elapsedtimebetweenballmoves has units milliseconds.
       ball_a_control_clock.Interval = elapsedtimebetweenballmoves;
       ball_a_control_clock.Enabled = true;
       ball_a_clock_active = true;
   }

   protected void Updatedisplay(System.Object sender, ElapsedEventArgs evt)
   {
       Invalidate();
      if(!(ball_a_clock_active))
          {graphic_area_refresh_clock.Enabled = false;
           System.Console.WriteLine("The graphical area is no longer refreshing.  You may close the window.");
          }
   }
   protected void Updateballa(System.Object sender, ElapsedEventArgs evt)
   {
      if (start_active == true)
      {
          ball_a_real_coord_x = ball_a_real_coord_x + ball_a_horizontal_delta;
          ball_a_real_coord_y = ball_a_real_coord_y - ball_a_vertical_delta;
          ball_a_int_coord_x = (int)System.Math.Round(ball_a_real_coord_x);
          ball_a_int_coord_y = (int)System.Math.Round(ball_a_real_coord_y);
      }

      radians = Math.Atan2(ball_a_vertical_delta, ball_a_horizontal_delta);
      degrees = (int)(radians * (180 / Math.PI));

      if (ball_a_int_coord_y >= 630)
      {   
          ball_a_vertical_delta = 1.0;
      }
      if (ball_a_int_coord_x >= 1050)
      {
          ball_a_horizontal_delta = -1.0;
      }
      if (ball_a_int_coord_x <= 90)
      {
          ball_a_horizontal_delta = 1.0;
      }
      if (ball_a_int_coord_y <= 70)
      {
          ball_a_vertical_delta = -1.0;
      }
      updateCoords();

      if(ball_a_int_coord_x >= formwidth || ball_a_int_coord_y + 2*ball_a_radius <= 0 || ball_a_int_coord_y >= formheight)
          {ball_a_clock_active = false;
           ball_a_control_clock.Enabled = false;
           System.Console.WriteLine("The clock controlling ball a has stopped.");
          }
   }
   protected void updateCoords()
   {_xCoord.Text = "X: " + ball_a_int_coord_x.ToString();
    _yCoord.Text = "Y: " + ball_a_int_coord_y.ToString();}
   protected void start_fn(Object sender, EventArgs events)
   {
       ball_a_control_clock.Enabled = true;
       ball_a_clock_active = true;
       graphic_area_refresh_clock.Enabled = true;
       start_active = true;
       Startgraphicclock(graphicrefreshrate);
       Startballaclock(ball_a_update_rate);
   }
   protected void exit_fn(Object sender, EventArgs events)
   {
       Close();
   }
   protected void reset_fn(Object sender, EventArgs events)
   {
       ball_a_clock_active = false;
       ball_a_real_coord_x = 550;
       ball_a_real_coord_y = 350;
       _xCoord.Text = ball_a_real_coord_x.ToString();
       _yCoord.Text = ball_a_real_coord_y.ToString();
       _speed.Text = "";
       graphicrefresh.Text = "";
       _OneDirection.Text = "";
       ball_a_vertical_delta = -1.0;
       ball_a_horizontal_delta = 0.0;
       start_active = false;

   }
}



