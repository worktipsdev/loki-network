using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Windows.Forms;

namespace network.worktips.worktipsnet.win32.ui
{
    public partial class main_frame : Form
    {
        public static Process worktipsNetDaemon = new Process();
        public static bool isConnected;
        public static string logText;
        private string config_path;
        private LogDumper ld;

        void UpdateUI(string text)
        {
            this.Invoke(new MethodInvoker(delegate () { worktipsnetd_fd1.AppendText(text); }));
        }

        public main_frame()
        {
            InitializeComponent();
            if (Program.platform == PlatformID.Win32NT)
                config_path = Environment.ExpandEnvironmentVariables("%APPDATA%\\.worktipsnet");
            else
                config_path = Environment.ExpandEnvironmentVariables("%HOME%/.worktipsnet");
            StatusLabel.Text = "Disconnected";
            var build = ((AssemblyInformationalVersionAttribute)Assembly
  .GetAssembly(typeof(main_frame))
  .GetCustomAttributes(typeof(AssemblyInformationalVersionAttribute), false)[0])
  .InformationalVersion;
            UIVersionLabel.Text = String.Format("Worktipsnet version {0}", build);
            worktipsnetd_fd1.Text = string.Empty;
            logText = string.Empty;
            worktipsNetDaemon.OutputDataReceived += new DataReceivedEventHandler((s, ev) =>
            {
                if (!string.IsNullOrEmpty(ev.Data))
                {
                    UpdateUI(ev.Data + Environment.NewLine);
                }
            });
        }

        private void btnConfigProfile_Click(object sender, EventArgs e)
        {
            //MessageBox.Show("not implemented yet", "error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
            UserSettingsForm f = new UserSettingsForm();
            f.ShowDialog();
            f.Dispose();
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            string worktipsnetExeString;

            if (Program.platform == PlatformID.Win32NT)
                worktipsnetExeString = String.Format("{0}\\worktipsnet.exe", Directory.GetCurrentDirectory());
            else
                worktipsnetExeString = String.Format("{0}/worktipsnet", Directory.GetCurrentDirectory());

            worktipsNetDaemon.StartInfo.UseShellExecute = false;
            worktipsNetDaemon.StartInfo.RedirectStandardOutput = true;
            //worktipsNetDaemon.EnableRaisingEvents = true;
            worktipsNetDaemon.StartInfo.CreateNoWindow = true;
            worktipsNetDaemon.StartInfo.FileName = worktipsnetExeString;
            worktipsNetDaemon.Start();
            worktipsNetDaemon.BeginOutputReadLine();
            btnConnect.Enabled = false;
            TrayConnect.Enabled = false;
            StatusLabel.Text = "Connected";
            isConnected = true;
            NotificationTrayIcon.Text = "Worktipsnet - connected";
            btnDrop.Enabled = true;
            TrayDisconnect.Enabled = true;
            NotificationTrayIcon.ShowBalloonTip(5, "Worktipsnet", "Connected to network.", ToolTipIcon.Info);
        }

        private void btnDrop_Click(object sender, EventArgs e)
        {
            worktipsNetDaemon.CancelOutputRead();
            worktipsNetDaemon.Kill();
            btnConnect.Enabled = true;
            TrayConnect.Enabled = true;
            btnDrop.Enabled = false;
            TrayDisconnect.Enabled = false;
            StatusLabel.Text = "Disconnected";
            NotificationTrayIcon.Text = "Worktipsnet - disconnected";
            isConnected = false;
            logText = worktipsnetd_fd1.Text;
            worktipsnetd_fd1.Text = string.Empty;
            NotificationTrayIcon.ShowBalloonTip(5, "Worktipsnet", "Disconnected from network.", ToolTipIcon.Info);

        }

        private void worktipsnetd_fd1_TextChanged(object sender, EventArgs e)
        {
            if (Properties.Settings.Default.autoScroll)
                worktipsnetd_fd1.ScrollToCaret();
            else
                return;
        }

        private void btnHide_Click(object sender, EventArgs e)
        {
            Hide();
            if (isConnected)
                NotificationTrayIcon.ShowBalloonTip(5, "Worktipsnet", "Currently connected.", ToolTipIcon.Info);
            else
                NotificationTrayIcon.ShowBalloonTip(5, "Worktipsnet", "Currently disconnected.", ToolTipIcon.Info);
        }

        private void NotificationTrayIcon_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (!Visible)
            {
                Show();
            }
        }

        private void btnAbout_Click(object sender, EventArgs e)
        {
            AboutBox a = new AboutBox();
            a.ShowDialog(this);
            a.Dispose();
        }

        private void saveLogToFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (isConnected)
                MessageBox.Show("Cannot dump log when client is running.", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            else
            {
                if (logText == string.Empty)
                {
                    MessageBox.Show("Log is empty", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    return;
                }
                if (ld == null)
                    ld = new LogDumper(logText);
                else
                    ld.setText(logText);

                ld.CreateLog(config_path);
                MessageBox.Show(string.Format("Wrote log to {0}, previous log rotated", ld.getLogPath()), "Worktipsnet", MessageBoxButtons.OK, MessageBoxIcon.Information);
                logText = string.Empty;
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox a = new AboutBox();
            a.ShowDialog();
            a.Dispose();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void TrayDisconnect_Click(object sender, EventArgs e)
        {
            btnDrop_Click(sender, e);
        }

        private void TrayConnect_Click(object sender, EventArgs e)
        {
            btnConnect_Click(sender, e);
        }

        private void showToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Show();
        }
    }
}
