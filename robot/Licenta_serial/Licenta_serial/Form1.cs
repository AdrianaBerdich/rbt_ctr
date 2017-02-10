using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Licenta_serial
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            serialPort1.PortName = "COM7";
            serialPort1.BaudRate = 9600;
            serialPort1.Open();
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
            chart1.ChartAreas["ChartArea1"].AxisX.LabelStyle.Format = DateTime.Now.ToString("hh:mm:ss");
            chart1.ChartAreas["ChartArea1"].AxisY.Title = "Distanta";
            chart1.ChartAreas["ChartArea1"].AxisX.Title = "Timp";
        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        void desenare(float sp, float cv)
        {
           // chart1.Series["set point"].Points.Add(sp);
            chart1.Series["Turatie"].Points.Add(cv);
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadLine();
            string[] date = data.Split(',');
            float set_point = 20;// (float)(Convert.ToDecimal(date[1]));
            float currtent_position = (float)(Convert.ToDecimal(date[3]));



            //int v = int.Parse(w);

            if (data != String.Empty)
            {

                Invoke(new Action(() => textBox1.Clear()));
                Invoke(new Action(() => textBox1.AppendText(date[0] + "  ")));
                Invoke(new Action(() => textBox2.Clear()));
                Invoke(new Action(() => textBox2.AppendText(date[1] + "  ")));
                Invoke(new Action(() => textBox3.Clear()));
                Invoke(new Action(() => textBox3.AppendText(date[2] + "  ")));
                Invoke(new Action(() => textBox4.Clear()));
                Invoke(new Action(() => textBox4.AppendText(date[3] + "  ")));
                // Invoke(new Action(() => textBox3.AppendText(date[2] + "  ")));
                BeginInvoke((Action)(() => desenare(set_point, currtent_position)));
            }
        }
    }
}
