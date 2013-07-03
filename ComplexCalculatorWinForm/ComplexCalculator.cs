using System;
using System.ComponentModel;
using System.Text;
using System.Windows.Forms;
using System.Globalization;
using System.Text.RegularExpressions;
using ComplexCalculatorWinForm.Utils; 

namespace ComplexCalculatorWinForm
{
    public partial class ComplexCalculatorMain : Form
    {
        #region Init 
        public ComplexCalculatorMain()
        {
            InitializeComponent();
            statusCopy.Text = ComplexCalculatorWinForm.Properties.Resources.Statusstrip;
        }

        #endregion

        #region Definitions
        
        /// <summary>
        /// Mathematical operations
        /// </summary>
        enum Operation
        {
            add,
            substract,
            multiply,
            divide
        }; 

        /// <summary>
        /// Complexnumber Part 1
        /// </summary>
        ComplexNumber fPart;

        /// <summary>
        /// Complexnumber Part 2
        /// </summary>
        ComplexNumber sPart;
        
        /// <summary>
        /// Reg Ex for Input Validation 
        /// Validates true if input is typeof(double)
        /// Allows german comma and mathematical dot
        /// </summary>
        private readonly Regex doubleInput = new Regex("^[+-]?([0-9]*(\\.|,)?[0-9]+|[0-9]+(\\.|,)?[0-9]*)([eE][+-]?[0-9]+)?$"); 

        #endregion
            
        #region Operations

        /// <summary>
        /// Calculates complex numbers by given operation
        /// </summary>
        /// <param name="operation"></param>
        private void Calculate(Operation operation)
        {
            if (OnlyDigits())
            {
                fPart = new ComplexNumber(Convert.ToDouble(tnum1.Text), Convert.ToDouble(timag1.Text));
                sPart = new ComplexNumber(Convert.ToDouble(tnum2.Text), Convert.ToDouble(timag2.Text));

                switch (operation)
                {
                    case Operation.add:
                        setResultText(ComplexNumber.Add(fPart, sPart));
                        break;

                    case Operation.substract:
                        setResultText(ComplexNumber.Subtract(fPart, sPart));
                        break;

                    case Operation.multiply:
                        setResultText(ComplexNumber.Multiply(fPart, sPart));
                        break;

                    case Operation.divide:

                        try
                        {
                            setResultText(ComplexNumber.Divide(fPart, sPart));
                        }

                        catch (DivideByZeroException)
                        {
                            setResultText(false);
                        }

                        break;

                    default:
                        break;
                }
            }

            else
            {
                MessageBox.Show("Fehlerhafte Eingabe in den Feldern, bitte nur Zahlen benutzen!", "Warnung", MessageBoxButtons.OK, MessageBoxIcon.Warning); 
            }
            
        }

        /// <summary>
        /// Sets the resultlabel text by given result
        /// </summary>
        /// <param name="cResult"></param>
        /// <param name="divisionByZero"></param>
        private void setResultText(ComplexNumber cResult)
        {
           result.Text = "Das Ergebnis lautet: " + cResult.ToString();
        }

        /// <summary>
        /// Sets error in resultlabel if division is not legit
        /// </summary>
        /// <param name="legit"></param>
        private void setResultText(bool legit)
        {
            if(!legit) 
            {
                result.Text = "Division durch 0 ist nicht erlaubt!";
            }
        }

        /// <summary>
        /// Digitvalidation for Textfields by RegEx doubleInput
        /// </summary>
        /// <returns></returns>
        private bool OnlyDigits()
        {
            if (doubleInput.IsMatch(tnum1.Text) && doubleInput.IsMatch(tnum2.Text) && doubleInput.IsMatch(timag1.Text) && doubleInput.IsMatch(timag2.Text))
            {
                return true; 
            }

            return false; 
        }

        #endregion
                
        #region Button Events

        private void neueBerechnungToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            tnum1.Text = "";
            tnum2.Text = "";
            timag1.Text = "";
            timag2.Text = "";
            result.Text = "";
        }

        private void beendenToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void überToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show(ComplexCalculatorWinForm.Properties.Resources.Copyright);
        }

        private void btnMultiply_Click_1(object sender, EventArgs e)
        {
            Calculate(Operation.multiply); 
        }

        private void btnDivide_Click_1(object sender, EventArgs e)
        {
            Calculate(Operation.divide); 
        }

        private void btnAdd_Click_1(object sender, EventArgs e)
        {
            Calculate(Operation.add);
        }

        private void btnSubstract_Click_1(object sender, EventArgs e)
        {
            Calculate(Operation.substract);
        }

        #endregion
    }
}
