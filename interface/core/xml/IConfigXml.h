/*! \file IConfigXml.h
 *  \brief Define the interface for xml data initialization: IConfigXml
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_XML_ICONFIGXML_H_
#define X3_XML_ICONFIGXML_H_

#include <objptr.h>

BEGIN_NAMESPACE_X3

const char* const clsidXmlFile = "7ef2fa9e-fdc4-4a10-a786-c9f51f4910b5";

class IConfigData;
class IConfigSection;
class IFileCryptHandler;

//! The interface for xml data initialization.
/*! This interface can be casted to IConfigData or IConfigTransaction.\n
    May use IFileCryptHandler to change xml file's reading and writing.
    \interface IConfigXml
    \ingroup _GROUP_PLUGIN_XML_
    \see x3::clsidXmlFile, IConfigData, IConfigTransaction
*/
class IConfigXml : public IObject
{
public:
    X3DEFINE_IID(IConfigXml);

    //! Return the configure data object.
    virtual IConfigData* GetData() = 0;

    //! Return file name (see SetFileName).
    virtual std::wstring GetFileName() const = 0;

    //! Set file name for reading or saving.
    /*! Call this before reading or saving.
        \param filename absolute file name, or Web Service URL.
    */
    virtual void SetFileName(const wchar_t* filename) = 0;

    //! Return the root element name.
    /*! When the xml file hasn't been loaded, this function will temporarily load it,
        and the result name may be different from SetRootName().
        \return the actual root element name.
        \see SetRootName, Reload
    */
    virtual std::wstring GetRootName() const = 0;

    //! Set the root element name and xml encoding.
    /*!
        \param rootName the root element name, 
            used to verify xml structure while reading.\n
            If rootName is empty then not comparing the root element name.
        \param encoding xml encoding used while creating new document.
        \param nmspace xml namespace name used while creating new document.
        \see GetRootName, Reload
    */
    virtual void SetRootName(const wchar_t* rootName = L"root", 
        const wchar_t* encoding = L"UTF-8", 
        const wchar_t* nmspace = L"") = 0;

    //! Set the schema file location for creating new document.
    /*!
        \param location the schema file location, can be relative file name.
        \see GetRootName, Reload
    */
    virtual void SetSchemaLocation(const wchar_t* location) = 0;

    //! Reload xml document regardless changes.
    /*! This function will verify the root element name when SetRootName() is called before,
        thus returns false if the root element name is different from SetRootName().
        \return true if loading successful, otherwise returns false and create new document.
    */
    virtual bool Reload() = 0;

    //! Save this document to a file.
    /*! This function doesn't change the modified status of this document.
        \param filename absolute file name to save, 
            empty string is represented as the current file name.
        \return true if saving successful.
    */
    virtual bool Save(const wchar_t* filename = L"") const = 0;

    //! Get xml content of the whole document.
    /*! It'll auto call Reload() when the document hasn't been loaded.
        \param[out] content xml content that hasn't xml encoding text.
        \return true if successful.
    */
    virtual bool GetXmlContent(std::wstring& content) const = 0;

    //! Load document from the string content.
    /*! This function will verify the root element name when SetRootName() is called before.
        \param content the xml content, auto skip the UNICODE flags.
        \return true if loading successful, otherwise returns false and create new document.
    */
    virtual bool SetXmlContent(const std::wstring& content) = 0;

    //! Get xml content of a element node.
    /*!
        \param[out] content xml content that hasn't xml encoding text.
        \param[in] node the element node.
        \return true if successful.
    */
    virtual bool GetXmlContent(std::wstring& content, IConfigSection* node) const = 0;

    //! Set file encryption handler.
    /*! Call the handler before loading file or after saving file.
        \param[in] handler new encryption handler.
        \return old encryption handler.
    */
    virtual IFileCryptHandler* SetCryptHandler(IFileCryptHandler* handler) = 0;
};

END_NAMESPACE_X3
#endif // X3_XML_ICONFIGXML_H_
