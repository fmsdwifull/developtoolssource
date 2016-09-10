<?php

/**
 * This is the model class for table "func".
 *
 * The followings are the available columns in table 'func':
 * @property string $Function_ID
 * @property integer $Module_ID
 * @property string $Function_Name
 * @property string $Desciption
 * @property string $Parameter
 * @property string $ReturnValue
 * @property integer $Enabled
 * @property integer $createdby
 * @property string $createdtime
 */
class Func extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return Func the static model class
	 */
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	/**
	 * @return string the associated database table name
	 */
	public function tableName()
	{
		return 'func';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('Module_ID, Enabled, createdby', 'numerical', 'integerOnly'=>true),
			array('Function_Name', 'length', 'max'=>50),
			array('Desciption, Parameter, ReturnValue', 'length', 'max'=>100),
			array('createdtime', 'safe'),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('Function_ID, Module_ID, Function_Name, Desciption, Parameter, ReturnValue, Enabled, createdby, createdtime', 'safe', 'on'=>'search'),
		);
	}

	/**
	 * @return array relational rules.
	 */
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'Function_ID' => 'Function',
			'Module_ID' => 'Module',
			'Function_Name' => 'Function Name',
			'Desciption' => 'Desciption',
			'Parameter' => 'Parameter',
			'ReturnValue' => 'Return Value',
			'Enabled' => 'Enabled',
			'createdby' => 'Createdby',
			'createdtime' => 'Createdtime',
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;

		$criteria->compare('Function_ID',$this->Function_ID,true);
		$criteria->compare('Module_ID',$this->Module_ID);
		$criteria->compare('Function_Name',$this->Function_Name,true);
		$criteria->compare('Desciption',$this->Desciption,true);
		$criteria->compare('Parameter',$this->Parameter,true);
		$criteria->compare('ReturnValue',$this->ReturnValue,true);
		$criteria->compare('Enabled',$this->Enabled);
		$criteria->compare('createdby',$this->createdby);
		$criteria->compare('createdtime',$this->createdtime,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}