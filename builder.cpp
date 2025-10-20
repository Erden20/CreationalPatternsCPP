#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Report {
private:
    string header;
    string content;
    string footer;
public:
    void setHeader(const string& h) { header = h; }
    void setContent(const string& c) { content = c; }
    void setFooter(const string& f) { footer = f; }

    void show() const {
        cout << "\n=== Отчет ===\n";
        cout << header << "\n";
        cout << content << "\n";
        cout << footer << "\n";
        cout << "=============\n";
    }

    string getHTML() const {
        return "<html><body><h1>" + header + "</h1><p>" + content +
               "</p><footer>" + footer + "</footer></body></html>";
    }
};

class IReportBuilder {
public:
    virtual void setHeader(const string& header) = 0;
    virtual void setContent(const string& content) = 0;
    virtual void setFooter(const string& footer) = 0;
    virtual unique_ptr<Report> getReport() = 0;
    virtual ~IReportBuilder() = default;
};

class TextReportBuilder : public IReportBuilder {
private:
    unique_ptr<Report> report;
public:
    TextReportBuilder() { report = make_unique<Report>(); }
    void setHeader(const string& header) override { report->setHeader("📝 " + header); }
    void setContent(const string& content) override { report->setContent(content); }
    void setFooter(const string& footer) override { report->setFooter("— " + footer); }
    unique_ptr<Report> getReport() override { return move(report); }
};

class HtmlReportBuilder : public IReportBuilder {
private:
    unique_ptr<Report> report;
public:
    HtmlReportBuilder() { report = make_unique<Report>(); }
    void setHeader(const string& header) override { report->setHeader(header); }
    void setContent(const string& content) override { report->setContent(content); }
    void setFooter(const string& footer) override { report->setFooter(footer); }
    unique_ptr<Report> getReport() override { return move(report); }
};

class ReportDirector {
public:
    void constructReport(IReportBuilder& builder) {
        builder.setHeader("Отчет о продажах");
        builder.setContent("Продажи за октябрь выросли на 20%.");
        builder.setFooter("Компания «TechStore», 2025");
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ReportDirector director;

    TextReportBuilder textBuilder;
    director.constructReport(textBuilder);
    auto textReport = textBuilder.getReport();
    textReport->show();

    HtmlReportBuilder htmlBuilder;
    director.constructReport(htmlBuilder);
    auto htmlReport = htmlBuilder.getReport();

    cout << "\n=== HTML версия отчета ===\n";
    cout << htmlReport->getHTML() << "\n";

    return 0;
}
