using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Mnvn.WebAppDockerTest.Ultis;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace Mnvn.WebAppDockerTest.api
{
    [Route("api/[controller]")]
    [ApiController]
    public class FfmpegController : ControllerBase
    {
        IConfiguration _appSettings;

        static char[] _spliter = new char[] { '/', '\\' };
        public FfmpegController(IConfiguration configuration)
        {
            _appSettings = configuration;
        }

        [HttpPost]
        public async Task<string> Convert2mp4(IFormFile file)
        {
            var dirwww = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "wwwroot").Replace("\\", "/");

            var dirTemp = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "temp").Replace("\\", "/");

            if (Directory.Exists(dirTemp) == false) Directory.CreateDirectory(dirTemp);

            var dirShared = Path.Combine(dirwww, "shared").Replace("\\", "/");

            if (Directory.Exists(dirShared) == false) Directory.CreateDirectory(dirShared);

            //MemoryStream ms = new MemoryStream();
            //await file.CopyToAsync(ms);
            //ms.Position = 0;

            var fileName = file.FileName;
            var idx = file.FileName.LastIndexOfAny(_spliter);
            if (idx > 0)
            {
                fileName = fileName.Substring(idx).Trim(_spliter);
            }
            fileName = $"{DateTime.Now.ToString("yyyyMMddHHmmss")}-{Guid.NewGuid()}-{fileName}";

            var srcFile = Path.Combine(dirTemp, fileName).Replace("\\", "/");
            var sf = System.IO.File.Create(srcFile);
            await file.CopyToAsync(sf);
            sf.Flush();
            sf.Close();

            var desFile = Path.Combine(dirShared, fileName).Replace("\\", "/")+ ".mp4";
            var cmdR = await new CommandExecutor().Run($"-i \"{srcFile}\" \"{desFile}\"");

            return JsonConvert.SerializeObject(new
            {
                ok = 1,
                msg = "ok",
                desFile = desFile.Replace(dirwww,""),
                logs = cmdR
            });
        }
    }
}
