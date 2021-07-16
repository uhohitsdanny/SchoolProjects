using System;
using System.Windows.Forms;            //Needed for "Application" near the end of Main function.
public class Movingball
{  public static void Main()
   {  System.Console.WriteLine("The animated ball moving program will begin now.");
      Oneobjectsframe motionapplication = new Oneobjectsframe();
      Application.Run(motionapplication);
      System.Console.WriteLine("This animated program has ended.  Bye.");
   }
}
