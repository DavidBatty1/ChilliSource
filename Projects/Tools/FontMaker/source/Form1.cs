﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace FontTool
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            this.fontDialog1.ShowApply = false;
            this.fontDialog1.AllowSimulations = false;
            this.fontNameBox.Text = this.fontDialog1.Font.Name + "-" + this.fontDialog1.Font.ToString();

            this.fontColourDialog.AnyColor = true;
            this.fontColourDialog.AllowFullOpen = true;
            this.fontColourDialog.Color = Color.White;
            
            this.richTextBox1.ForeColor = Color.White;

			string strNumbers = "1234567890";
			string strAlphabet = "abcdefghijklmnopqrstuvwxyz";
			string strSymbols = "+-*/=.,_?!\"'£$%^&*()@#:;~";

			string defaultCharacters = strNumbers + strAlphabet + strAlphabet.ToUpper() + strSymbols;

			this.CharactersToIncludeBox.Text = defaultCharacters;

            SetupColour();
        }

        private void OnSelectFontPressed(object sender, EventArgs e)
        {
            this.fontDialog1.ShowDialog();
            this.richTextBox1.Font = this.fontDialog1.Font;
            this.fontNameBox.Text = this.fontDialog1.Font.Name + "-" + this.fontDialog1.Font.SizeInPoints.ToString();
        }

        private void OnPickColour(object sender, EventArgs e)
        {
            PresentFontColour();
        }

        private void PresentFontColour()
        {
            fontColourDialog.Color = FontColourSample.BackColor;
            fontColourDialog.ShowDialog();
            SetupColour();
        }

        private void SetupColour()
        {
            Color textColour = fontColourDialog.Color;

            this.richTextBox1.ForeColor = textColour;
            if (AutoPreviewBackColour.Checked)
            {
                this.richTextBox1.BackColor = PreviewBGColourForFontColour(textColour);
            }
            
            FontColourSample.BackColor = textColour;
            
        }

        Color PreviewBGColourForFontColour(Color colour)
        {
            if (colour.GetBrightness() > 0.5f)
            {
                return Color.DarkGray;
            }
            else
            {
                return Color.LightGray;
            }
        }

        string GetCharactersToOutput()
        {
            List<char> uniqueChars = new List<char>();

            foreach (char c in CharactersToIncludeBox.Text)
            {
                if (!uniqueChars.Contains(c) && !Char.IsWhiteSpace(c))
                    uniqueChars.Add(c);
            }

            return new string(uniqueChars.ToArray());
        }

        private void OnExportPreviousPressed(object sender, EventArgs e)
        {
            CreateEmptyTempFolder();

            FolderBrowserDialog fb = new FolderBrowserDialog();
            fb.Description = "Choose the directory of the individual images";

            if (fb.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            DirectoryInfo dir = new DirectoryInfo(fb.SelectedPath);

            foreach (FileInfo file in dir.GetFiles())
            {
                file.CopyTo("Temp/" + file.Name);
            }

            DialogResult result = this.saveFileDialog1.ShowDialog();

            if (result != DialogResult.OK)
            {
                return;
            }

            BuildTempContents(this.saveFileDialog1.FileName);
        }

        private void CreateEmptyTempFolder()
        {
            if (Directory.Exists("Temp"))
            {
                DirectoryInfo dir = new DirectoryInfo("Temp");

                foreach (FileInfo file in dir.GetFiles())
                {
                    File.Delete(file.FullName);
                }
            }
            else
            {
                Directory.CreateDirectory("Temp");
            }
        }

        private void DeleteTempFolder()
        {
            if (Directory.Exists("Temp"))
            {
                DirectoryInfo dir = new DirectoryInfo("Temp");

                foreach (FileInfo file in dir.GetFiles())
                {
                    File.Delete(file.FullName);
                }

                try
                {
                    Directory.Delete("Temp");
                }
                catch (Exception e)
                {
                    //When testing on Mac the thumb.db is in use causing this to fail
                }
            }
        }

        private void OnExportPressed(object sender, EventArgs e)
        {
            string CharsToOutput = GetCharactersToOutput();

            if (string.IsNullOrEmpty(CharsToOutput))
                return;

            DialogResult result = this.saveFileDialog1.ShowDialog();

            if (result != DialogResult.OK)
            {
                return;
            }

            CreateEmptyTempFolder();

            //Render and save out glyphs to our temp         
            List<Bitmap> glyphs = RenderGlyphs(CharsToOutput);

            for (int nChar = 0; nChar < CharsToOutput.Length; nChar++)
            {
                string name = string.Format("{0:x4}", (int)CharsToOutput[nChar]).ToUpperInvariant();
                using (FileStream imageFile = File.Create("Temp/" + name.ToString() + ".png"))
                {
                    glyphs[nChar].Save(imageFile, System.Drawing.Imaging.ImageFormat.Png);
                }
            }

            BuildTempContents(this.saveFileDialog1.FileName);
        }

        private void BuildTempContents (string outputName)
		{
			//Invoke Java font tool
			string strJavaCommand = "java";
			string strJarArgument = "-jar FontTool.jar ";
            string strArgs = "--input Temp/ --padding 2 --divisibleby 4 --maxwidth " + this.maxSizeTextBox.Text + " --maxheight " + this.maxSizeTextBox.Text + " --output " + outputName + " --fontHeight " + this.fontDialog1.Font.Height + " --premultiply 1";

            Process p = new Process();
            p.StartInfo.FileName = strJavaCommand;
            p.StartInfo.Arguments = strJarArgument + strArgs;
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory();
            p.Start();
			p.WaitForExit();

            DeleteTempFolder();
        }

        private void OnSavePressed(object sender, EventArgs e)
        {
            string CharsToOutput = GetCharactersToOutput();

            if (string.IsNullOrEmpty(CharsToOutput))
                return;

            FolderBrowserDialog fb = new FolderBrowserDialog();
            fb.Description = "Choose a directory in which to save the individual images";

            if (fb.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            Directory.CreateDirectory(fb.SelectedPath);

            //Render and pack glyphs
            List<Bitmap> glyphs = RenderGlyphs(CharsToOutput);

            //Save individual glyph files
            for (int nChar = 0; nChar < CharsToOutput.Length; nChar++)
            {
                string name = string.Format("{0:x4}", (int)CharsToOutput[nChar]).ToUpperInvariant();
                using (FileStream imageFile = File.Create(fb.SelectedPath + "/" + name.ToString() + ".png"))
                {
                    glyphs[nChar].Save(imageFile, System.Drawing.Imaging.ImageFormat.Png);
                }
            }
        }

        List<Bitmap> RenderGlyphs(string str) 
        {
            GlyphRenderer glyphRenderer = new GlyphRenderer();
            glyphRenderer.HighQualityRendering = enableAntialiasing.Checked;

            glyphRenderer.Font = fontDialog1.Font;
            glyphRenderer.TextColour = FontColourSample.BackColor;

            glyphRenderer.DrawShadow = enableDropshadows.Checked;
            if (glyphRenderer.DrawShadow)
            {
                glyphRenderer.ShadowColour = shadowColourSample.BackColor;
                
                glyphRenderer.ShadowXOffset = XShadowOffset;
                glyphRenderer.ShadowYOffset = YShadowOffset;
            }

            glyphRenderer.DrawOutline = enableOutline.Checked;
            if (glyphRenderer.DrawOutline)
            {
                glyphRenderer.OutlineColour = outlineColourSample.BackColor;
                glyphRenderer.OutlineThickness = 1; 
            }

            return glyphRenderer.RenderGlyphs(str);
        }

        private void TextColorSample_Click(object sender, EventArgs e)
        {
            PresentFontColour();
        }

        #region AutoPreview UI
        private void AutoPreviewColour_CheckedChanged(object sender, EventArgs e)
        {
            PreviewBGButton.Enabled = !AutoPreviewBackColour.Checked;
            PreviewBGColour.Enabled = !AutoPreviewBackColour.Checked;

            if (AutoPreviewBackColour.Checked)
            {
                this.richTextBox1.BackColor = PreviewBGColourForFontColour(FontColourSample.BackColor);
            }
            else
            {
                this.richTextBox1.BackColor = PreviewBGColour.BackColor;
            }
        }

        private void PresentPreviewBGColour(object sender, EventArgs e)
        {
            fontColourDialog.Color = PreviewBGColour.BackColor;
            fontColourDialog.ShowDialog();
            PreviewBGColour.BackColor = fontColourDialog.Color;
            richTextBox1.BackColor = fontColourDialog.Color;
        }
        #endregion
        #region Shadow UI Logic
        private void EnableDropshadows_CheckedChanged(object sender, EventArgs e)
        {
            bool enableShadowControls = enableDropshadows.Checked;
            shadowColourButton.Enabled = enableShadowControls;
            shadowColourSample.Enabled = enableShadowControls;
            shadowXOffsetLabel.Enabled = enableShadowControls;
            shadowXOffsetText.Enabled = enableShadowControls;
            shadowYOffsetLabel.Enabled = enableShadowControls;
            shadowYOffsetText.Enabled = enableShadowControls;

            if (enableShadowControls)
            {
                enableOutline.Checked = false;
            }
        }

        private void ShadowXOffsetText_TextChanged(object sender, EventArgs e)
        {
            int result;
            if (!int.TryParse(shadowXOffsetText.Text, out result))
            {
                result = 0;
            }
            XShadowOffset = result;
        }

        private void ShadowYOffsetText_TextChanged(object sender, EventArgs e)
        {
            int result;
            if (!int.TryParse(shadowYOffsetText.Text, out result))
            {
                result = 0; 
            }

            YShadowOffset = result;
        }

        int XShadowOffset = 1;
        int YShadowOffset = 1;

        private void PresentShadowColour(object sender, EventArgs e)
        {
            fontColourDialog.Color = shadowColourSample.BackColor;
            fontColourDialog.ShowDialog();
            shadowColourSample.BackColor = fontColourDialog.Color;
        }

        #endregion

        private void EnableOutline_CheckedChanged(object sender, EventArgs e)
        {
            bool enableOutlineControls = enableOutline.Checked;

            outlineColourButton.Enabled = enableOutlineControls;
            outlineColourSample.Enabled = enableOutlineControls;
            outlineThicknessLabel.Enabled = enableOutlineControls;
            outlineThicknessText.Enabled = enableOutlineControls;

            if (enableOutlineControls)
            {
                enableDropshadows.Checked = false;
            }
        }

        private void PresentOutlineColour(object sender, EventArgs e)
        {
            fontColourDialog.Color = outlineColourSample.BackColor;
            fontColourDialog.ShowDialog();
            outlineColourSample.BackColor = fontColourDialog.Color;
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void maxSizeTextBox_TextChanged(object sender, EventArgs e)
        {
            try
            {
                int maxSize = Convert.ToInt32(this.maxSizeTextBox.Text);
            }
            catch (FormatException)
            {
                MessageBox.Show("Error!", "String must be a number");
                this.maxSizeTextBox.Text = "4096";
            }
            catch (OverflowException)
            {
                MessageBox.Show("Error!", "String must a number less than 2,147,483,647");
                this.maxSizeTextBox.Text = "4096";
            }
        }
    }
}
