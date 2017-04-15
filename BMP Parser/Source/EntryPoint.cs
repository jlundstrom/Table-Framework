using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Drawing;
using System.IO;

namespace BMPtoArray
{
    class EntryPoint
    {
        static void Main(string[] args)
        {
            string[] fileEntries;
            Trace.Listeners.Add(new TextWriterTraceListener(Console.Out));
            Trace.AutoFlush = true;
            Trace.Indent();
            ConfigStorage configSettings;
            configSettings = ReadInConfig();
            if (null == configSettings)
            {
                Trace.WriteLine("Impressive failure in ReadInConfig");
                return;
            }
            if (Int32.Parse(configSettings.Mode) == 1)
            {
                try
                {
                    Directory.CreateDirectory(configSettings.OutputDirectory);
                    fileEntries = Directory.GetFiles(@configSettings.SourceDirectory, configSettings.FileName);
                    FileStream fs = new FileStream((string.Concat(configSettings.OutputDirectory, "output.txt")), FileMode.Append);
                    StreamWriter wo = new StreamWriter(fs);
                    for (int f = 0; f < fileEntries.Length; f++)
                    {
                        Bitmap img = new Bitmap(fileEntries[f]);
                        wo.Write("char    ");
                        wo.Write(Path.GetFileNameWithoutExtension(fileEntries[f]));
                        wo.Write("["+ img.Width + "]"+ "[" + img.Height + "]"+" = {");
                        for (int i = 0; i < img.Width; i++)
                        {
                            wo.Write(" {");
                            for (int j = 0; j < img.Height; j++)
                            {

                                Color pixel = img.GetPixel(i, j);
                                if (Threshold(pixel))
                                {
                                    wo.Write(" 1");
                                }
                                else
                                {
                                    wo.Write(" 0");
                                }
                                if(j+1 < img.Height)
                                {
                                    wo.Write(",");
                                }
                            }
                            wo.Write(" }");
                            if (i + 1 < img.Width)
                            {
                                wo.Write(",");
                            }
                        }
                        wo.Write(" };\n");
                    }
                    wo.Close();
                }
                catch
                {
                    Trace.WriteLine("Something messed up in parsing/outputting");
                    return;
                }
                return;
            }
            else if(Int32.Parse(configSettings.Mode) == 2)
            {
                try
                {
                    Directory.CreateDirectory(configSettings.OutputDirectory);
                    fileEntries = Directory.GetFiles(@configSettings.SourceDirectory, configSettings.FileName);
                    FileStream fs = new FileStream((string.Concat(configSettings.OutputDirectory, "output.txt")), FileMode.Append);
                    StreamWriter wo = new StreamWriter(fs);
                    for (int f = 0; f < fileEntries.Length; f++)
                    {
                        Bitmap img = new Bitmap(fileEntries[f]);
                        wo.Write("char    ");
                        wo.Write(Path.GetFileNameWithoutExtension(fileEntries[f]));
                        wo.Write("[" + img.Width + "]" + "[" + img.Height + "]" +"[3]" +" = {");
                        for (int i = 0; i < img.Width; i++)
                        {
                            wo.Write(" {");
                            for (int j = 0; j < img.Height; j++)
                            {
                                Color pixel = img.GetPixel(i, j);
                                wo.Write("{"+pixel.R+", ");
                                wo.Write( pixel.G + ", ");
                                wo.Write(pixel.B + "} ");
                                if (j + 1 < img.Height)
                                {
                                    wo.Write(",");
                                }
                            }
                            wo.Write(" }");
                            if (i + 1 < img.Width)
                            {
                                wo.Write(",");
                            }
                        }
                        wo.Write(" };\n");
                    }
                    wo.Close();
                }
                catch
                {
                    Trace.WriteLine("Something messed up in parsing/outputting");
                    return;
                }
                return;
            }
           else
            {
                Trace.WriteLine("Mode config incorrect");
                return;
            }


            return;
        }
        public static ConfigStorage ReadInConfig()
        {
            ConfigStorage configSettings;
            configSettings = new ConfigStorage();
            XmlDocument config = new XmlDocument();
            XmlNode node;
            try
            {
                config.Load(string.Concat((AppDomain.CurrentDomain.BaseDirectory), ("config.xml")));
                try
                {
                    node = config.SelectSingleNode("Config");
                    configSettings.SourceDirectory = String.Concat(node.SelectSingleNode("SourceDirectory").InnerText, "\\");
                    configSettings.FileName = node.SelectSingleNode("FileName").InnerText;
                    configSettings.Mode = node.SelectSingleNode("Mode").InnerText;
                    configSettings.OutputDirectory = String.Concat(node.SelectSingleNode("OutputDirectory").InnerText, "\\");
                    return configSettings;
                }
                catch
                {
                    Trace.WriteLine("Error reading in config");
                }
            }
            catch
            {
                Trace.WriteLine("Config file not found");
            }
            return null;
        }
        public static bool Threshold(Color Pixel)
        {
            if (Pixel.R<100 && Pixel.G<100 && Pixel.B <100)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    }
    class ConfigStorage
    {
        private string sourceDirectory;
        private string fileName;
        private string outputDirectory;
        private string mode;

        public string SourceDirectory
        {
            get
            {
                return sourceDirectory;
            }

            set
            {
                sourceDirectory = value;
            }
        }

        public string FileName
        {
            get
            {
                return fileName;
            }

            set
            {
                fileName = value;
            }
        }

        public string OutputDirectory
        {
            get
            {
                return outputDirectory;
            }

            set
            {
                outputDirectory = value;
            }
        }

        public string Mode
        {
            get
            {
                return mode;
            }

            set
            {
                mode = value;
            }
        }
    }
}
