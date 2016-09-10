<?php

/**
 * This is the model class for table "modules".
 *
 * The followings are the available columns in table 'modules':
 * @property integer $module_id
 * @property string $module_name
 * @property integer $type
 * @property string $desciption
 * @property string $remarks
 * @property string $requirements
 * @property string $link
 * @property string $supporter
 * @property integer $createdby
 * @property integer $modifiedby
 * @property string $createdtime
 * @property string $modifiedtime
 * @property integer $enabled
 */
class Modules extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return Modules the static model class
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
		return 'modules';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('module_id, type, createdby, modifiedby, enabled', 'numerical', 'integerOnly'=>true),
			array('module_name', 'length', 'max'=>50),
			array('desciption, remarks, requirements, link, supporter, createdtime, modifiedtime', 'safe'),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('module_id, module_name, type, desciption, remarks, requirements, link, supporter, createdby, modifiedby, createdtime, modifiedtime, enabled', 'safe', 'on'=>'search'),
			
			array('link',
				'file',    //定义为file类型
				'allowEmpty'=>true, 
				//'types'=>'*',   //上传文件的类型
				'maxSize'=>1024*1024*10*3,    //上传大小限制，注意不是php.ini中的上传文件大小
				'tooLarge'=>'文件大于30M，上传失败！请上传小于30M的文件！'
			),
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
			'module_id' => 'Module',
			'module_name' => 'Module Name',
			'type' => 'Type',
			'desciption' => 'Desciption',
			'remarks' => 'Remarks',
			'requirements' => 'Requirements',
			'link' => 'Link',
			'supporter' => 'Supporter',
			'createdby' => 'Createdby',
			'modifiedby' => 'Modifiedby',
			'createdtime' => 'Createdtime',
			'modifiedtime' => 'Modifiedtime',
			'enabled' => 'Enabled',
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

		$criteria->compare('module_id',$this->module_id);
		$criteria->compare('module_name',$this->module_name,true);
		$criteria->compare('type',$this->type);
		$criteria->compare('desciption',$this->desciption,true);
		$criteria->compare('remarks',$this->remarks,true);
		$criteria->compare('requirements',$this->requirements,true);
		$criteria->compare('link',$this->link,true);
		$criteria->compare('supporter',$this->supporter,true);
		$criteria->compare('createdby',$this->createdby);
		$criteria->compare('modifiedby',$this->modifiedby);
		$criteria->compare('createdtime',$this->createdtime,true);
		$criteria->compare('modifiedtime',$this->modifiedtime,true);
		$criteria->compare('enabled',$this->enabled);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}