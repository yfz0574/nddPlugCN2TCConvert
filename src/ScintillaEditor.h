//
// Created by Zh1an on 2023/2/9.
//

#ifndef JSONVIEW_SCINTILLAEDITOR_H
#define JSONVIEW_SCINTILLAEDITOR_H

#include <string>
#include <functional>

class QsciScintilla;

class ScintillaEditor
{
public:
    explicit ScintillaEditor(const std::function<QsciScintilla* ()>& cb);

    ~ScintillaEditor() = default;

public:
    [[nodiscard]] std::string getchText();

    [[nodiscard]] bool ischFile() const;

    void replaceSelection(const std::string& text);

    void replaceAll(const std::string& text) const;

    void makeSelection(size_t start, size_t end);

    [[nodiscard]] auto getSelectionStart() const->size_t;

    [[nodiscard]] auto getSelectionEnd() const->size_t;

    [[nodiscard]] auto getEOL() const -> unsigned;

    [[nodiscard]] auto getIndent() const->std::tuple<char, unsigned>;
    int getCodePage();//取当前编辑文件的代码页，以此判断是否如utf-8
private:
    void refreshSelectionPos();

private:
    std::function<QsciScintilla* ()> scintillaCallback_;

    size_t startPos_ = 0;
    size_t endPos_ = 0;
};

#endif    // JSONVIEW_SCINTILLAEDITOR_H