using System;
using TekWorxAPI;
namespace TekWorkxDeviceApiTest
{
    internal class Program
    {
        /// <summary>
        /// Cihazlara erişim sağlayan DLL'in (wrapper'ın) nesnesi
        /// </summary>
        public static Device CovisartA320Api;
        static void Main(string[] args)
        {
            CovisartA320Api = new Device();
            Console.ReadLine();
            try
            {
                int errorCode = CovisartA320Api.OpenControllers();
            }
            catch (Exception ex)
            {

                Console.WriteLine(ex.Message);
            }
        }
    }
}
