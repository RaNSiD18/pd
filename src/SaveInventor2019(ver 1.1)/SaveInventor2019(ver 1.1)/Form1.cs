using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Inventor;
using System.Windows.Forms;
using System.IO;
using Application = System.Windows.Forms.Application;
using File = System.IO.File;

namespace SaveInventor2019_ver_1._1_
{
    public partial class Form1 : Form
    {
        private const string NAME_PROJECT = "SaveProjectInventor";

        private Inventor.Application ThisApplication = null;

        public Form1()
        {
            InitializeComponent();
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
        }

        private void SaveProject()
        {
            try
            {
                //Проверка наличия активного состояния Инвентора.
                ThisApplication = (Inventor.Application)System.Runtime.InteropServices.Marshal.GetActiveObject("Inventor.Application");
            }
            catch
            {
                // Если Инвентор не открыт, то возвращаемся в основную программу.
                System.Windows.Forms.MessageBox.Show("Запустите Инвентор!");
            }


            if (ThisApplication.ActiveDocument.FileSaveCounter == 0)
            {
                MessageBox.Show("Открылось внутреннее окно сохранения Inventor");
                // Первое сохранение детали
                ThisApplication.ActiveDocument.Save();
            }
            else
            {
                saveFileDialog1.FileName = ThisApplication.ActiveDocument.DisplayName;
                saveFileDialog1.Filter = "Inventor Part Document|*.ipt|Inventor Part Document|*.step|Inventor Part Document|*.stp";
                saveFileDialog1.Title = NAME_PROJECT;
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    if (!string.IsNullOrWhiteSpace(saveFileDialog1.FileName))
                    {
                        //ThisApplication.ActiveDocument.Save2(false, saveFileDialog1.FileName);
                        ThisApplication.ActiveDocument.SaveAs(saveFileDialog1.FileName, false);
                        MessageBox.Show("Файл " + ThisApplication.ActiveDocument.DisplayName + " сохранился по пути \n" + saveFileDialog1.FileName);
                    }
                }
            }
        }

        private void buSaveModel_Click(object sender, EventArgs e)
        {
            SaveProject();
        }

        private void ConvertProject()
        {
            openFileDialog1.FileName = "";
            openFileDialog1.Filter = "Inventor Part Document|*.ipt";
            openFileDialog1.Title = NAME_PROJECT;
            openFileDialog1.InitialDirectory = "c:\\";
            openFileDialog1.RestoreDirectory = true;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                File.Move(openFileDialog1.FileName, openFileDialog1.FileName.Replace(".ipt", ".step"));// переименование файла
                MessageBox.Show("Файл " + openFileDialog1.FileName + " изменен на \n" + openFileDialog1.FileName.Replace(".ipt", ".step"));
            }
        }

        private void buConvertModel_Click(object sender, EventArgs e)
        {
            ConvertProject();
        }

        private void OpenProject()
        {
            openFileDialog1.FileName = "";
            openFileDialog1.Filter = "Inventor Part Document|*.ipt|Inventor Part Document|*.step|Inventor Part Document|*.stp";
            openFileDialog1.Title = NAME_PROJECT;
            openFileDialog1.InitialDirectory = "c:\\";
            openFileDialog1.RestoreDirectory = true;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                var name = openFileDialog1.FileName;
                System.Diagnostics.Process.Start(@name);
            }
        }

        private void buOpenModel_Click(object sender, EventArgs e)
        {
            OpenProject();
        }
    }
}
