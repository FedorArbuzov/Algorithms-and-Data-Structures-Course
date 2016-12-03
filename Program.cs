using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace test_cpp
{
            
    class Program
    {
        
        static void Main(string[] args)
        {
            Random rnd1 = new Random();
        
            

            string path1 = "";
            string path2 = "";
            string path3 = "";
            string folder = @"C:\Users\user\.CLion2016.2\system\cmake\generated\kdz1-5fe3508b\5fe3508b\Debug\";

            char[] alphaENG = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ".ToCharArray();

            char[] alphaENG_RUS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ".ToCharArray();

            char[] alphaENG_RUS_SP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ!@#$%^&*()_+\\|{}[]/-\"".ToCharArray();

            for (int i = 20; i <= 100; i += 20) {
                path1 = folder + "test_cpp_" + Convert.ToString(1) + "_" + Convert.ToString(i) + "KB.txt";

                path2 = folder + "test_cpp_" + Convert.ToString(2) + "_" + Convert.ToString(i) + "KB.txt";

                path3 = folder + "test_cpp_" + Convert.ToString(3) + "_" + Convert.ToString(i) + "KB.txt";
                if(!File.Exists(path1))
                {
                    // Create a file to write to.
                    using (StreamWriter sw = File.CreateText(path1))
                    {
                        for (int i1 = 0; i1 < i * 1024; i1++)
                        {
                            sw.Write(alphaENG[rnd1.Next(alphaENG.Length)]);
                        }
                    }
                }
                if (!File.Exists(path2))
                {
                    // Create a file to write to.
                    using (StreamWriter sw = File.CreateText(path2))
                    {
                        for (int i1 = 0; i1 < i * 1024; i1++)
                        {
                            sw.Write(alphaENG_RUS[rnd1.Next(alphaENG_RUS.Length)]);
                        }
                    }
                }
                if (!File.Exists(path3))
                {
                    // Create a file to write to.
                    using (StreamWriter sw = File.CreateText(path3))
                    {
                        for (int i1 = 0; i1 < i * 1024; i1++)
                        {
                            sw.Write(alphaENG_RUS_SP[rnd1.Next(alphaENG_RUS_SP.Length)]);
                        }
                    }
                }
                Console.WriteLine("test_cr");
                
            }
            var p = new Process { StartInfo = new ProcessStartInfo { FileName = "C:\\Users\\user\\.CLion2016.2\\system\\cmake\\generated\\kdz1-5fe3508b\\5fe3508b\\Debug\\kdz1.exe", Arguments = "1 example", UseShellExecute = false, CreateNoWindow = true } };
            p.Start();
            Console.ReadKey();
        }
    }
}
