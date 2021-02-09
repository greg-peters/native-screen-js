# Screen-js
This project is designed to be a cross platform NodeJS display solution that supports multiple displays.

<ul> 
  <li>Goal 1: Develop cross platform display api to query multiple physical displays</li>
  <li>Goal 2: Detect which display currently has focus</li>
  <li>Goal 3: Screen capture support for active display</li>
</ul>

## Supported Platforms
<ul>
  <li>Mac OSX or later</li>
  <li>Windows 2000 or later</li>
</ul>

## Requirements
Install Yarn<br/>
`npm install yarn -g`<br/><br/>
Compile<br/>
`yarn`<br/><br/>
Run Demo<br/>
`node test.js`<br/><br/>

## Output
```
{
  "displayCount": 1,
  "screens": [
    {
      "modelNumber": 43298, <--- OSX Only
      "isBuiltIn": 1,
      "isMainDisplay": 1,
      "width": 1440,
      "height": 900,
      "x": 0,  <--- Top left corner of display in virtual space
      "y": 0,  <--- Top left corner of display in virtual space
      "rotation": 0 <--- OSX Only
    }
  ]
}
```
