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

namespace SaveInventor2019_ver_1._1_
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// ThisApplication - Объект для определения активного состояния Инвентора
        /// </summary>
        private Inventor.Application ThisApplication = null;
        /// <summary>
        /// Словарь для хранения ссылок на документы деталей
        /// </summary>
        //private Dictionary<string, PartDocument> oPartDoc = new Dictionary<string, PartDocument>();
        /// <summary>
        /// Словарь для хранения ссылок на определения деталей
        /// </summary>
        //private Dictionary<string, PartComponentDefinition> oCompDef = new Dictionary<string, PartComponentDefinition>();
        /// <summary>
        /// Словарь для хранения ссылок на инструменты создания деталей
        /// </summary>
        //private Dictionary<string, TransientGeometry> oTransGeom = new Dictionary<string, TransientGeometry>();
        /// <summary>
        /// Словарь для хранения ссылок на транзакции редактирования
        /// </summary>
        //private Dictionary<string, Transaction> oTrans = new Dictionary<string, Transaction>();
        /// <summary>
        /// Словарь для хранения имен сохраненных документов деталей
        /// </summary>
        //private Dictionary<string, string> oFileName = new Dictionary<string, string>();

        //private AssemblyDocument oAssemblyDocName;

        public Form1()
        {
            InitializeComponent();
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;

            try
            {
                //Проверка наличия активного состояния Инвентора.
                ThisApplication = (Inventor.Application)System.Runtime.InteropServices.Marshal.GetActiveObject("Inventor.Application");
                if (ThisApplication != null) MessageBox.Show("Инвентор открыт!", "SaveProjectInventor");
            }
            catch
            {
                // Если Инвентор не запущен, то возвращаемся в основную программу.
                MessageBox.Show("Запустите Инвентор!", "SaveProjectInventor");
            }
        }

        private void GetExtrudeFeature()
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
                return;
            }

            String oName = "Test_save_project";

            String dir = "C:\\Users\\serwa\\Desktop\\";

            int i = 0;
            if (i < 100)
            {

                /// 
                //ThisApplication.ActiveDocument.SaveAs(dir + oName + "_" + i + ".ipt", true);
                //MessageBox.Show("Файл " + oName + "_" + i + ".ipt" + " сохранился по пути \n" + dir);
                ThisApplication.ActiveDocument.DisplayName = "Test_save_project_" + i;

                saveFileDialog1.FileName = ThisApplication.ActiveDocument.DisplayName;
                saveFileDialog1.Filter = "Inventor Part Document|*.*";
                saveFileDialog1.Title = oName;
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    if (!string.IsNullOrWhiteSpace(saveFileDialog1.FileName))
                    {
                        ThisApplication.ActiveDocument.SaveAs(saveFileDialog1.FileName, false);
                        MessageBox.Show("Файл " + ThisApplication.ActiveDocument.DisplayName + " сохранился по пути \n" + saveFileDialog1.FileName);
                        i++;
                    }
                }
            }
        }

        private void buSaveModel_Click(object sender, EventArgs e)
        {
            GetExtrudeFeature();
        }
    }
}
