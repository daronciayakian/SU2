#pragma once
#include <string>

/** \brief Enum to identify the screen output format. */
enum class ScreenOutputFormat {
  INTEGER,         /*!< \brief Integer format. Example: 34 */
  FIXED,           /*!< \brief Format with fixed precision for floating point values. Example: 344.54  */
  SCIENTIFIC,      /*!< \brief Scientific format for floating point values. Example: 3.4454E02 */
  PERCENT          /*!< \brief Format with fixed precision for floating point values with a % signs. Example: 99.52% */
};

/** \brief Enum to identify the screen/history field type. */
enum class FieldType {
  RESIDUAL,         /*!< \brief A user-defined residual field type*/
  AUTO_RESIDUAL,    /*!< \brief An automatically generated residual field type */
  COEFFICIENT,      /*!< \brief User defined coefficient field type  */
  AUTO_COEFFICIENT, /*!< \brief Automatically generated coefficient field type  */
  CUSTOM_EVAL,      /*!< \brief Custom evaluation field */
  CUSTOM_INTEGRATE, /*!< \brief Custom integration field */
  CUSTOM_SURFACE_INTEGRATE,
  SURFACE_INTEGRATE,
  DEFAULT           /*!< \brief Default field type */
};

class COutputField {

public:
  /*! \brief The name of the field, i.e. the name that is printed in the screen or file header.*/
  std::string         fieldName = "";
  /*! \brief The group this field belongs to. */
  std::string         outputGroup  ="";
  /*! \brief String containing the description of the field */
  std::string         description = "";
  /*! \brief The field type*/
  FieldType    fieldType = FieldType::DEFAULT;
  /*! \brief The value of the field. */
  su2double           value = 0.0;
  /*! \brief The format that is used to print this value to screen. */
  ScreenOutputFormat  screenFormat = ScreenOutputFormat::FIXED;
  /*! \brief This value identifies the position of the values of this field at each node in the ::Local_Data array. */
  short       offset;

  packToken* tokenRef = nullptr;

  interpreter::UserFunction* userFunction = nullptr;

  COutputField() = default;

  COutputField(std::string fieldName_, FieldType type_, std::string OutputGroup_, std::string description_)
    : fieldName(std::move(fieldName_)), outputGroup(std::move(OutputGroup_)),  description(std::move(description_)),
      fieldType(type_), value(0.0)
  {}

  /*! \brief Constructor to initialize all members. */
  COutputField(std::string fieldName_, ScreenOutputFormat screenFormat_, std::string OutputGroup_,
                     FieldType fieldType_, std::string description_): COutputField(std::move(fieldName_), fieldType_, std::move(OutputGroup_), std::move(description_))
  {screenFormat = screenFormat_;}

  COutputField(std::string fieldName_, int offset_, std::string volumeOutputGroup_, std::string description_, FieldType type_):
     COutputField(std::move(fieldName_), type_, std::move(volumeOutputGroup_), std::move(description_))
  {offset = offset_;}
};
