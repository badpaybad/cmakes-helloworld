using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Mnvn.WebAppDockerTest.Ultis;
using Newtonsoft.Json;
using System;
using System.Drawing;
using System.IO;
using System.Threading.Tasks;

namespace Mnvn.WebAppDockerTest.Controllers
{
    public class HomeController : Controller
    {
        IConfiguration _appSettings;

        public HomeController(IConfiguration configuration)
        {
            _appSettings = configuration;
        }
        public async Task<IActionResult> Index()
        {
           
            string ffmpegTest = "";

            try {
                ffmpegTest = await new CommandExecutor().Run("ffmpeg -version");
            }
            catch(Exception ex)
            {
                ffmpegTest += "\r\nffmpeg -version\r\n" + JsonConvert.SerializeObject(ex);
                try
                {
                    ffmpegTest = await new CommandExecutor().Run("-version");
                }
                catch (Exception ex1)
                {
                    ffmpegTest += "\r\n-version\r\n" + JsonConvert.SerializeObject(ex1);
                }
            }
            
            string filename = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "wwwroot/1.jpg").Replace("\\", "/");
            Bitmap bmp = new Bitmap(filename);

            var resize = new Bitmap(bmp, bmp.Width / 4, bmp.Height / 4);
            MemoryStream ms = new MemoryStream();
            resize.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
            ms.Position = 0;
            var html = $"<br><img src='data:image/png;base64,{Convert.ToBase64String(ms.ToArray())}'><br>{ffmpegTest}";

            

            return View("Index", html);
        }

        

    }
}
