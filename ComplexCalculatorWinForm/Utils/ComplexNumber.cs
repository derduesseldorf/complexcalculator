using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ComplexCalculatorWinForm.Utils
{
    class ComplexNumber
    {
        const int MAXFLOATINGPOINT = 3; 
        public double Real { get; set; }
        public double Imag { get; set; }

        /// <summary>
        /// New Complexnumber 
        /// </summary>
        public ComplexNumber()
        {

        }

        /// <summary>
        /// New <see cref="ComplexNumber"/>
        /// </summary>
        /// <param name="real"></param>
        /// <param name="imag"></param>
        public ComplexNumber(double real, double imag)
        {
            this.Real = real;
            this.Imag = imag; 
        }

        /// <summary>
        /// Add operation for two ComplexNumbers
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>ComplexNumber</returns>
        public static ComplexNumber Add(ComplexNumber a, ComplexNumber b) 
        {
            double real, imag;
            real = a.Real + b.Real;
            imag = a.Imag + b.Imag; 
            return new ComplexNumber(real, imag); 
        }

        /// <summary>
        /// Subtract operation for two ComplexNumbers
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>ComplexNumber</returns>
        public static ComplexNumber Subtract(ComplexNumber a, ComplexNumber b)
        {
            double real, imag;
            real = a.Real - b.Real;
            imag = a.Imag - b.Imag;
            return new ComplexNumber(real, imag);
        }

        /// <summary>
        /// Multiply operation for two ComplexNumbers
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>ComplexNumber</returns>
        public static ComplexNumber Multiply(ComplexNumber a, ComplexNumber b)
        {
            double real, imag;
            real = a.Real * b.Real - a.Imag * b.Imag;
            imag = a.Real * b.Imag + a.Imag * b.Real;
            return new ComplexNumber(real, imag);
        }

        /// <summary>
        /// Divide operation for two ComplexNumbers
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns>ComplexNumber</returns>
        public static ComplexNumber Divide(ComplexNumber a, ComplexNumber b)
        {
            double real, imag;
            if (b.Real != 0 && b.Imag != 0)
            {
                real = (a.Real * b.Real + a.Imag * b.Imag) / (b.Real * b.Real + b.Imag * b.Imag);
                imag = (a.Imag * b.Real - a.Real * b.Imag) / (b.Real * b.Real + b.Imag * b.Imag);
            }

            else throw new DivideByZeroException();
            return new ComplexNumber(real, imag);
        }

        public override string ToString()
        {
            string r = Math.Round(Real, MAXFLOATINGPOINT).ToString();
            string i = Math.Round(Imag, MAXFLOATINGPOINT).ToString();

            return r + " + " + i + "i"; 
        }
    }
}
