using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;

namespace Mnvn.WebAppDockerTest.Ultis
{

    public class CommandExecutor
    {
        public event Action<string> OnStdOut;
        List<Process> _cmds = new List<Process>();

        public static bool IsWindows()
        {
            return Environment.OSVersion.Platform == PlatformID.Win32NT ||
                   Environment.OSVersion.Platform == PlatformID.Win32S ||
                   Environment.OSVersion.Platform == PlatformID.Win32Windows ||
                   Environment.OSVersion.Platform == PlatformID.WinCE;
        }

        public async Task<string> Run(string args,string exe= "ffmpeg")
        {
            Stopwatch sw = Stopwatch.StartNew();
            string dir = AppDomain.CurrentDomain.BaseDirectory;

            System.Diagnostics.Process cmd = new System.Diagnostics.Process();
            _cmds.Add(cmd);

            cmd.StartInfo.CreateNoWindow = true;
            cmd.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            cmd.StartInfo.WorkingDirectory = dir;
            cmd.StartInfo.RedirectStandardInput = true;
            cmd.StartInfo.RedirectStandardOutput = true;
            cmd.StartInfo.RedirectStandardError = true;
            cmd.StartInfo.UseShellExecute = false;
            //if (IsWindows() == false)
            //{

            //}
            //else
            //{
            //    cmd.StartInfo.FileName = "cmd.exe";
            //}

            cmd.StartInfo.FileName = exe;
            cmd.StartInfo.Arguments = args;

            //cmd.StartInfo.FileName = cmdLine;
            //cmd.StartInfo.StandardErrorEncoding = Encoding.UTF8;
            //cmd.StartInfo.StandardOutputEncoding = Encoding.Unicode;
            //cmd.StartInfo.StandardInputEncoding = Encoding.Unicode;
            cmd.Start();

            //cmd.StandardInput.WriteLine("chcp 65001");
            //await cmd.StandardInput.WriteLineAsync(cmdLine);

            await cmd.StandardInput.FlushAsync();
            cmd.StandardInput.Close();

            var output = new List<string>();

            cmd.OutputDataReceived += new DataReceivedEventHandler(
                (s, e) =>
                {
                    if (!string.IsNullOrEmpty(e.Data))
                    {
                        output.Add(e.Data);
                        OnStdOut?.Invoke(e.Data);
                    }
                });
            cmd.ErrorDataReceived += new DataReceivedEventHandler(
                (s, e) =>
                {
                    if (!string.IsNullOrEmpty(e.Data))
                    {
                        output.Add(e.Data);
                        OnStdOut?.Invoke(e.Data);
                    }
                });

            cmd.BeginOutputReadLine();
            cmd.BeginErrorReadLine();
            cmd.WaitForExit();

            try
            {
                cmd.Close();
            }
            catch
            {
            }

            try
            {
                cmd.Kill();
            }
            catch { }

            sw.Stop();

            string outstring = string.Join("\r\n", output.ToArray());

            bool isOk = outstring.IndexOf("Error", StringComparison.OrdinalIgnoreCase) <= 0;

            if (!isOk)
            {
                Console.WriteLine("WARNING: " + outstring);
            }

            return outstring;
        }

    }
}
